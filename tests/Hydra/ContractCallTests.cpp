// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.
//
// This is a GENERATED FILE, changes made here MAY BE LOST.
// Generated one-time (codegen/bin/cointests)
//

#include "../interface/TWTestUtilities.h"
#include <gtest/gtest.h>
#include "Hydra/TokenScriptBuilder.h"
#include "HexCoding.h"


TEST(ContractInput, TestInput){
    auto gasLimit = 1000;
    auto toAddress = "HPjtxTZwy8i4emXxb64hz82x3s6q48LbGz";
    auto amount = 10;
    auto contractAddress = "4ab26aaa1803daa638910d71075c06386e391147";

    Hydra::Proto::ContractInput input;

    input.set_gas_limit(gasLimit);
    input.set_to(toAddress);
    input.set_amount(amount);
    input.set_contract_address(contractAddress);

    std::string expected = "";
    auto res = TW::Hydra::TokenScriptBuilder::buildTokenScript(input);

    {
        ASSERT_EQ(hex(res.bytes), expected);
    }
}

