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
#include "../Bitcoin/TxComparisonHelper.h"
#include "Hydra/TransactionBuilder.h"
#include "Bitcoin/TransactionInput.h"
#include "Bitcoin/Transaction.h"
#include "Bitcoin/SegwitAddress.h"
#include "Bitcoin/TransactionSigner.cpp"
#include "Data.h"
#include "PrivateKey.h"
#include "ComparisonHelper.h"

#include <gtest/gtest.h>
#include<vector>
#include<map>

using namespace TW;
TEST(Hydra, ContractTokenScript){

    auto res = buildTokenScript(1000, "HPjtxTZwy8i4emXxb64hz82x3s6q48LbGz", 10, "4ab26aaa1803daa638910d71075c06386e391147");

    std::string expected = "0x548203e8a9059cbb0000000000000000000000005878623634687a3832783373367134384c62477a000000000000000000000000000000000000000000000000000000000000000aa83461623236616161313830336461613633383931306437313037356330363338366533393131343781c2";

    {
        ASSERT_EQ(hexEncoded(res.bytes), expected);
    }
}

TEST(Hydra, TestTransactionPlanBuilding){
    std::vector<int64_t> amounts = {200, 300, 800, 1000};
    auto utxos = buildTestHydraUTXOs(amounts);
    auto signingInput = buildHydraSigningInput(100, 1, utxos, false, TWCoinTypeHydra);

    std::map<std::string, Bitcoin::Script> scripts = {{"contract", buildTokenScript(1000, "HPjtxTZwy8i4emXxb64hz82x3s6q48LbGz", 10, "4ab26aaa1803daa638910d71075c06386e391147")}};
    signingInput.scripts = scripts;

    auto plan = Hydra::TransactionBuilder::plan(signingInput);
    
    {

       ASSERT_EQ(plan.utxos.size(), 1);
       ASSERT_EQ(hexEncoded(plan.contract.bytes), "0x548203e8a9059cbb0000000000000000000000005878623634687a3832783373367134384c62477a000000000000000000000000000000000000000000000000000000000000000aa83461623236616161313830336461613633383931306437313037356330363338366533393131343781c2");
    }
}

TEST(Hydra, TestTransactionBuilder){
    
    std::vector<int64_t> amounts = {12545182455, 19152684041};
    auto utxos = buildTestHydraUTXOs(amounts);
    auto signingInput = buildHydraSigningInput(1, 3600, utxos, false, TWCoinTypeHydra);

    std::map<std::string, Bitcoin::Script> scripts = {{"contract", buildTokenScript(1000, "HPjtxTZwy8i4emXxb64hz82x3s6q48LbGz", 10, "4ab26aaa1803daa638910d71075c06386e391147")}};
    signingInput.scripts = scripts;

    auto plan = Hydra::TransactionBuilder::plan(signingInput);

    auto transaction = Hydra::TransactionBuilder::build<Bitcoin::Transaction>(plan, "HGQWcFAkv4WEC5dyknxrv6ZoPhD3rMCRdg", "HGQWcFAkv4WEC5dyknxrv6ZoPhD3rMCRdg", TWCoinTypeHydra,0);
    
    
    {
        ASSERT_EQ(plan.amount, 1);
        ASSERT_EQ(plan.change, 12544368854);
        ASSERT_EQ(plan.fee, 813600);
        ASSERT_EQ(plan.utxos.size(), 1);
        ASSERT_EQ(transaction.outputs.size(), 3); /* One output for the transction fee, one for the change and one for the contract call */

    }
    
}

TEST(Hydra, TestTransactionSigner){
    std::vector<int64_t> amounts = {12545182455, 19152684041};
    auto utxos = buildTestHydraUTXOs(amounts);
    auto signingInput = buildHydraSigningInput(1, 3600, utxos, false, TWCoinTypeHydra);

    std::map<std::string, Bitcoin::Script> scripts = {{"contract", buildTokenScript(1000, "HPjtxTZwy8i4emXxb64hz82x3s6q48LbGz", 10, "4ab26aaa1803daa638910d71075c06386e391147")}};
    signingInput.scripts = scripts;

    auto plan = Hydra::TransactionBuilder::plan(signingInput);
    

    //Sign
    auto result = Bitcoin::TransactionSigner<Bitcoin::Transaction, Hydra::TransactionBuilder>::sign(signingInput);
    std::cout << result.error() << std::endl;

    ASSERT_TRUE(result.isSuccess());
    auto signedTx = result.payload();

    Data serialized;
    signedTx.encode(serialized);
    EXPECT_EQ(getEncodedTxSize(signedTx), (EncodedTxSize{350, 240, 268}));
    ASSERT_EQ(hex(serialized),"0100000000010100000000000000000000000000000000000000000000000000000000000000000000000000ffffffff0301000000000000001976a91452ba7d3234ce242b1727b5d301125ab2cc0a3e1288acd6e0b3eb0200000016001422e6014ad3631f1939281c3625bc98db808fbfb0000000000000000073548203e8a9059cbb0000000000000000000000005878623634687a3832783373367134384c62477a000000000000000000000000000000000000000000000000000000000000000aa83461623236616161313830336461613633383931306437313037356330363338366533393131343781c2024830450221008f003dbf345d1127e723d748351b4aa5311fdaf3f8b7699877bed373a29cba8102201adf9842010ecd0eda5163f0bc6146e23c50e8db783662e079167d07a0e8b2d40121025cf26d221b01ca4d6040893b96f1dabfd2a108d449b3fa62854421f98a42562b00000000");
}

