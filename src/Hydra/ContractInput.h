// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include<string>
#include "../Bitcoin/Amount.h"
#include "../proto/Hydra.pb.h"

namespace TW::Hydra{

class ContractInput{
public:
    TW::Bitcoin::Amount gasLimit;

    TW::Bitcoin::Amount gasPrice;

    std::string to;
    
    TW::Bitcoin::Amount amount;

    ContractInput() = default;

    ContractInput(const Proto::ContractInput& input);

};

}