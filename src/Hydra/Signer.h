// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once
#include "../proto/Bitcoin.pb.h"
#include "../proto/Hydra.pb.h"

namespace TW::Hydra {


class Signer {
  public:
    Signer() = delete;

    /// Returns a transaction plan (utxo selection, fee estimation)
    static Bitcoin::Proto::TransactionPlan plan(const Hydra::Proto::SigningInput& input) noexcept;

    /// Signs a Proto::SigningInput transaction
    static Bitcoin::Proto::SigningOutput sign(const Hydra::Proto::SigningInput& input) noexcept;
};

} // namespace TW::Hydra
