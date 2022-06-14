// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "SigningInput.h"

using namespace TW;
using namespace TW::Hydra;

TW::Hydra::SigningInput::SigningInput(const Proto::SigningInput& input) 
: input(input.input())
, contract(input.contract())
{
    // input = Bitcoin::SigningInput(input.input());
    // contract = ContractInput(input.contract());
}