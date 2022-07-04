// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "../Data.h"
#include "OpCodes.h"
#include "ContractCallInput.h"
#include "../Ethereum/ABI.h"
#include "../Bitcoin/Script.h"

namespace TW::Hydra{

class TokenScript{
public:
    static TW::Bitcoin::Script buildTokenScript(int64_t gasLimit, const std::string& to, Data& amount, const std::string& contractAddress);

    static TW::Bitcoin::Script buildContractCallScript(int64_t gasLimit, const std::string& function, std::vector<ContractCallParam>& params, const std::string contractAddress);
};
}
