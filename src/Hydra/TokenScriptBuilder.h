// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once
#include "../proto/Hydra.pb.h"
#include "../Data.h"
#include "../Bitcoin/Script.h"


namespace TW::Hydra {

using ContractInput = Hydra::Proto::ContractInput;

class TokenScriptBuilder {
  public:
    /// Returns built token output
    static TW::Bitcoin::Script buildTokenScript(const ContractInput& input);

};

} // namespace TW::Hydra

//Wrapper for C interface
struct TWHydraTokenScript {
  TW::Hydra::TokenScriptBuilder impl;
};