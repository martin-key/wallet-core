// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.


#pragma once

#include "../Bitcoin/SigningInput.h"
#include "ContractInput.h"

namespace TW::Hydra{

class SigningInput{
public:
    TW::Bitcoin::SigningInput input;

    ContractInput contract;

    SigningInput() = default;
    SigningInput(const Proto::SigningInput& input);
};

}
