// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "../Bitcoin/SigningInput.h"
#include "../Bitcoin/Transaction.h"
#include "../Bitcoin/TransactionBuilder.h"
#include "../Bitcoin/InputSelector.h"
#include "SigningInput.h"
#include "TokenScript.h"
#include <TrustWalletCore/TWCoinType.h>

#include <optional>
#include <algorithm>

namespace TW::Hydra {

class TransactionBuilder {
public:
    /// Plans a transaction by selecting UTXOs and calculating fees.
    static Bitcoin::TransactionPlan plan(const TW::Hydra::SigningInput& input);
    /// Builds a transaction with the selected input UTXOs, and one main output and an optional change output.
    template <typename Transaction>
    static Bitcoin::Transaction build(const Bitcoin::TransactionPlan& plan, const std::string& toAddress,
                             const std::string& changeAddress, enum TWCoinType coin, uint32_t lockTime) {        
        coin = TWCoinTypeHydra;
        Transaction tx;

        if(plan.contract.bytes.size() > 0){
            if (plan.change > 0) {
                auto outputChange = Bitcoin::TransactionBuilder::prepareOutputWithScript(changeAddress, plan.change, coin);
                if (!outputChange.has_value()) { return {}; }
                tx.outputs.push_back(outputChange.value());
            }

            const auto emptyScript = Bitcoin::Script();
            for (auto& utxo : plan.utxos) {
                tx.inputs.emplace_back(utxo.outPoint, emptyScript, utxo.outPoint.sequence);
            }

            // Optional OP_RETURN output
            if (plan.outputOpReturn.size() > 0) {
                auto lockingScriptOpReturn = Bitcoin::Script::buildOpReturnScript(plan.outputOpReturn);
                tx.outputs.push_back(Bitcoin::TransactionOutput(0, lockingScriptOpReturn));
            }
            tx.outputs.push_back(Bitcoin::TransactionOutput(0,plan.contract));

        }else{
            tx = Bitcoin::TransactionBuilder::build<Bitcoin::Transaction>(plan, toAddress, changeAddress, coin, lockTime);
        }
        
        
        return tx;
    }
};

} // namespace TW::Hydra
