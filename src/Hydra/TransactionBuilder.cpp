#include "TransactionBuilder.h"
#include "TransactionSigner.h"

#include "Data.h"
#include "../Coin.h"
#include "../proto/Hydra.pb.h"

#include <algorithm>
#include <cassert>

namespace TW::Hydra{

// Above this number of UTXOs a simplified selection is used (optimization)
static const auto SimpleModeLimit = 1000;


/// Estimate encoded size by simple formula
int64_t estimateSimpleFee(const Bitcoin::FeeCalculator& feeCalculator, const Bitcoin::TransactionPlan& plan, int outputSize, int64_t byteFee) {
    return feeCalculator.calculate(plan.utxos.size(), outputSize, byteFee);
}

/// Estimate encoded size by invoking sign(sizeOnly), get actual size
int64_t estimateSegwitFee(const Bitcoin::FeeCalculator& feeCalculator, const Bitcoin::TransactionPlan& plan, int outputSize, const SigningInput& input) {
    TWPurpose coinPurpose = TW::purpose(static_cast<TWCoinType>(input.input.coinType));
    if (coinPurpose != TWPurposeBIP84) {
        // not segwit, return default simple estimate
        return estimateSimpleFee(feeCalculator, plan, outputSize, input.input.byteFee);
    }

    // duplicate input, with the current plan
    auto inputWithPlan = std::move(input);
    inputWithPlan.input.plan = plan;

    auto result = TransactionSigner::sign(inputWithPlan, true);
    if (!result) {
        // signing failed; return default simple estimate
        return estimateSimpleFee(feeCalculator, plan, outputSize, input.input.byteFee);
    }

    // Obtain the encoded size
    auto transaction = result.payload();
    Data dataNonSegwit;
    transaction.encode(dataNonSegwit, Bitcoin::Transaction::SegwitFormatMode::NonSegwit);
    int64_t sizeNonSegwit = dataNonSegwit.size();
    uint64_t vSize = 0;
    // Check if there is segwit
    if (!transaction.hasWitness()) {
        // no segwit, virtual size is defined as non-segwit size
        vSize = sizeNonSegwit;
    } else {
        Data dataWitness;
        transaction.encodeWitness(dataWitness);
        int64_t witnessSize = 2 + dataWitness.size();
        // compute virtual size:  (smaller) non-segwit + 1/4 of the diff (witness-only)
        // (in other way: 3/4 of (smaller) non-segwit + 1/4 of segwit size)
        vSize = sizeNonSegwit + witnessSize/4 + (witnessSize % 4 != 0);
    }
    uint64_t fee = input.input.byteFee * vSize;

    return fee;
}

int extraOutputCount(const Bitcoin::SigningInput& input) {
    int count = int(input.outputOpReturn.size() > 0);
    return count;
}

Bitcoin::TransactionPlan TransactionBuilder::plan(const TW::Hydra::SigningInput& signingInput){
    Bitcoin::TransactionPlan plan;
    auto input = signingInput.input;
    auto contract = signingInput.contract;
    auto contractCallInput = signingInput.contractCallInput;
    bool isTokenTransaction = false;
    if(contract.to != "" && contractCallInput.functionName == ""){
        isTokenTransaction = true;
        plan.contract = TokenScript::buildTokenScript(contract.gasLimit, contract.to, contract.amount ,input.toAddress);
        plan.amount = contract.gasLimit * contract.gasPrice;

    }else if(contractCallInput.functionName != ""){
        isTokenTransaction = true;
        plan.contract = TokenScript::buildContractCallScript(contractCallInput.gasLimit, contractCallInput.functionName, contractCallInput.parameters, input.toAddress);
        plan.amount = contractCallInput.gasLimit * contractCallInput.gasPrice;
        
        if(contractCallInput.functionName == "swapExactHYDRAForTokens"){
            plan.amount += input.amount;
        }
    }
    if(!isTokenTransaction){
        plan = Bitcoin::TransactionBuilder::plan(input);
    }else{
        if (input.utxos.empty()) {
            plan.error = Common::Proto::Error_missing_input_utxos;
        }else{

            const auto& feeCalculator = Bitcoin::getFeeCalculator(static_cast<TWCoinType>(input.coinType));
            auto inputSelector = Bitcoin::InputSelector<Bitcoin::UTXO>(input.utxos, feeCalculator);
            auto inputSum = Bitcoin::InputSelector<Bitcoin::UTXO>::sum(input.utxos);

            // if amount requested is the same or more than available amount, it cannot be satisifed, but
            // treat this case as MaxAmount, and send maximum available (which will be less)
            if (plan.amount > inputSum) {
                plan.error = Common::Proto::Error_not_enough_utxos;
            }

            auto extraOutputs = extraOutputCount(input);
            auto output_size = 2;
            Bitcoin::UTXOs selectedInputs;
           
            output_size = 2 + extraOutputs; // output + change
            if (input.utxos.size() <= SimpleModeLimit && input.utxos.size() <= Bitcoin::TransactionBuilder::MaxUtxosHardLimit) {
                selectedInputs = inputSelector.select(plan.amount, input.byteFee, output_size);
            } else {
                selectedInputs = inputSelector.selectSimple(plan.amount, input.byteFee, output_size);
            }
        
            if (selectedInputs.size() <= Bitcoin::TransactionBuilder::MaxUtxosHardLimit) {
                plan.utxos = selectedInputs;
            } else {
                // truncate to limit number of selected UTXOs
                plan.utxos.clear();
                for (auto i = 0; i < Bitcoin::TransactionBuilder::MaxUtxosHardLimit; ++i) {
                    plan.utxos.push_back(selectedInputs[i]);
                }
            }

            if (plan.utxos.size() == 0) {
                plan.amount = 0;
                plan.error = Common::Proto::Error_not_enough_utxos;
            } else {
                plan.availableAmount = Bitcoin::InputSelector<Bitcoin::UTXO>::sum(plan.utxos);

                // Compute fee.                
                plan.fee = estimateSegwitFee(feeCalculator, plan, output_size, signingInput);
               
                // Check if the contract call is swap, if true get the 
                if(contractCallInput.functionName == "swapExactHYDRAForTokens"){
                    plan.amount -= input.amount;
                }

                plan.fee += plan.amount;
                

                plan.amount = input.amount;

                if(plan.fee < 0){
                    plan.error = Common::Proto::Error_not_enough_utxos;
                    plan.amount = 0;

                }
                if(plan.fee > plan.availableAmount){
                    plan.error = Common::Proto::Error_low_balance;
                    plan.amount = 0;
                }

                // compute change
                plan.change = plan.availableAmount - plan.amount - plan.fee;
            }
        }
    }
    return plan;
}

}