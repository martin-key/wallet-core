// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "SigningInput.h"
#include "../Bitcoin/Transaction.h"
#include "TransactionBuilder.h"
#include "../KeyPair.h"
#include "../Result.h"
#include "../proto/Hydra.pb.h"


namespace TW::Hydra {

/// Frontend class for transaction planning, building, and signing
class TransactionSigner {
public:
    // Create plan for a transaction
    static Bitcoin::TransactionPlan plan(const Hydra::SigningInput& input);

    // Sign an unsigned transaction.  Plan it if needed beforehand.
    static Result<Bitcoin::Transaction, Common::Proto::SigningError> sign(const Hydra::SigningInput& input, bool estimationMode = false);
};

} // namespace TW::Hydra
