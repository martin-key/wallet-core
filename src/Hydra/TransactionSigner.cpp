// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "TransactionSigner.h"

#include "../Bitcoin/SignatureBuilder.h"

#include "TransactionBuilder.h"

using namespace TW;
using namespace Hydra;

Bitcoin::TransactionPlan TransactionSigner::plan(const SigningInput& input) {
    return TransactionBuilder::plan(input);
}

Result<Bitcoin::Transaction, Common::Proto::SigningError> TransactionSigner::sign(const Hydra::SigningInput& signingInput, bool estimationMode) {
    auto input = signingInput.input;
    Bitcoin::TransactionPlan plan;
    if (input.plan.has_value()) {
        plan = input.plan.value();
    } else {
        plan = TransactionBuilder::plan(signingInput);
    }
    auto transaction = TransactionBuilder::build<Bitcoin::Transaction>(plan, input.toAddress, input.changeAddress, input.coinType, input.lockTime);
    Bitcoin::SignatureBuilder<Bitcoin::Transaction> signer(std::move(input), plan, transaction, estimationMode);
    return signer.sign();
}