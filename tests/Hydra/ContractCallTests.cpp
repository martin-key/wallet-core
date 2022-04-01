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
#include "ComparisonHelper.h"
#include<vector>
#include "Bitcoin/TransactionInput.h"
#include "Bitcoin/Transaction.h"

using namespace TW;
TEST(Hydra, ContractTokenScript){

    auto res = buildTokenScript(1000, "HPjtxTZwy8i4emXxb64hz82x3s6q48LbGz", 10, "4ab26aaa1803daa638910d71075c06386e391147");

    std::string expected = "0x548203e8a9059cbb0000000000000000000000005878623634687a3832783373367134384c62477a000000000000000000000000000000000000000000000000000000000000000aa83461623236616161313830336461613633383931306437313037356330363338366533393131343781c2";

    {
        ASSERT_EQ(hexEncoded(res.bytes), expected);
    }
}

TEST(TokenTransaction, TestTransactionBuilder){
    auto po0 = OutPoint(parse_hex("94be46260220bce2872e3ad69f4b7828792a3db0a6f460a8e956d6ea379b011d"), 1) 
    auto po1 = OutPoint(parse_hex("7435b2e54bc8e1b0312cc721aaa321df3db59ea721db13188abb8787c1c30257"), 1) 
    Bitcoin::TransctionInputs utxos;
    utxos.push_back(Bitcoin::TransactionInput(po0, Bitcoin::Script(), 12545182455)) 
    utxos.push_back(Bitcoin::TransactionInput(po1, Bitcoin::Script(), 19152684041)) 

    //TODO do not create the objects but use only the 

}

