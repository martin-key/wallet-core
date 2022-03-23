// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "SigningInput.h"
#include "Transaction.h"
#include "TransactionPlan.h"
#include "InputSelector.h"
#include "../proto/Bitcoin.pb.h"
#include <TrustWalletCore/TWCoinType.h>

#include <optional>
#include <algorithm>

namespace TW::Hydra {

class TransactionBuilder {
public:
    /// Plans a transaction by selecting UTXOs and calculating fees.
    static TransactionPlan plan(const SigningInput& input){
        auto plan = Bitcoin::TransactionBuilder::plan(input);
        plan.contract = input.scripts.at("contract");
        return plan;
    }

    /// Builds a transaction with the selected input UTXOs, and one main output and an optional change output.
    template <typename Transaction>
    static Transaction build(const TransactionPlan& plan, const std::string& toAddress,
                             const std::string& changeAddress, enum TWCoinType coin, uint32_t lockTime) {        
        coin = TWCoinTypeHydra;
        Transaction tx = Bitcoin::TransactionBuilder::build<Transaction>(plan, toAddress, changeAddress, coin, lockTime);
        if(plan.contract.size() > 0){
            tx.outputs.push_back(new Bitcoin::TransactionOutput(0,plan.contract))
        }
        
        return tx;
    }
};

} // namespace TW::Hydra
