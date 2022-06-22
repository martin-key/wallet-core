// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include<string>
#include "../Bitcoin/Amount.h"
#include "../proto/Hydra.pb.h"
#include "../Data.h"
#include <vector>

namespace TW::Hydra{

class ContractCallParam{
public:
    std::string type;

    std::vector<Data> value;

    ContractCallParam() = default;

    ContractCallParam(const Proto::ContractCallParam& param);
};


class ContractCallInput {
public:
    Bitcoin::Amount gasPrice;
    Bitcoin::Amount gasLimit;

    std::string functionName;
    std::vector<ContractCallParam> parameters;

    ContractCallInput() = default;

    ContractCallInput(const Proto::ContractCallInput& input);
};

}