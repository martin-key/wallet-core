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
#include "Hydra/TransactionBuilder.h"
#include "Hydra/TransactionSigner.h"
#include "Hydra/SigningInput.h"
#include "Bitcoin/Transaction.h"
#include "Bitcoin/SegwitAddress.h"
#include "Data.h"
#include "PrivateKey.h"
#include "ComparisonHelper.h"
#include "uint256.h"
#include "AnyAddress.h"

#include <gtest/gtest.h>
#include<vector>
#include<string>
#include<map>

using namespace TW;


TEST(Hydra, TestRegularTransactionPlanBuilding){
    std::vector<int64_t> amounts = {20000000, 3000000, 8000000, 10000000};
    auto utxos = buildTestHydraUTXOs(amounts);
    auto bitcoinSigningInput = buildBitcoinSigningInput(100, 58, utxos, false, TWCoinTypeHydra);

    Hydra::SigningInput signingInput;
    signingInput.input = bitcoinSigningInput;

    auto plan = Hydra::TransactionBuilder::plan(signingInput);
    
    {
       ASSERT_EQ(plan.utxos.size(), 1);
    }
}
TEST(Hydra, TestTokenTransactionPlanBuilding){
    std::vector<int64_t> amounts = {20000000, 3000000, 8000000, 10000000};
    auto utxos = buildTestHydraUTXOs(amounts);
    auto bitcoinSigningInput = buildBitcoinSigningInput(100, 58, utxos, false, TWCoinTypeHydra, "4ab26aaa1803daa638910d71075c06386e391147");
    auto contractInput = buildHydraContractInput(100000, 32, std::string("HQMfzgnCPSitwMKFVSnrrdEhNjPXuKV7Hq"), 10000000);

    Hydra::SigningInput signingInput;
    signingInput.input = bitcoinSigningInput;
    signingInput.contract = contractInput;

    auto plan = Hydra::TransactionBuilder::plan(signingInput);
    
    {
       ASSERT_EQ(plan.utxos.size(), 1);
       ASSERT_EQ(hexEncoded(plan.contract.bytes), "0x5403a0860144a9059cbb000000000000000000000000c3a87d9b1201a1cba90fba12c315a3d2f25ddc110000000000000000000000000000000000000000000000000000000000989680144ab26aaa1803daa638910d71075c06386e391147c2");
    }
}

TEST(Hydra, TestContractCallTransactionPlanBuilding){
    std::vector<int64_t> amounts = {20000000, 3000000, 8000000, 10000000};
    auto utxos = buildTestHydraUTXOs(amounts);
    auto bitcoinSigningInput = buildBitcoinSigningInput(0, 58, utxos, false, TWCoinTypeHydra, "4ab26aaa1803daa638910d71075c06386e391147");

    auto contractCallParam1 = Hydra::ContractCallParam();
    contractCallParam1.type = "address[]";
    contractCallParam1.value.push_back(AnyAddress::dataFromString("HQMfzgnCPSitwMKFVSnrrdEhNjPXuKV7Hq", TWCoinTypeHydra));
    contractCallParam1.value.push_back(AnyAddress::dataFromString("HQMfzgnCPSitwMKFVSnrrdEhNjPXuKV7Hq", TWCoinTypeHydra));

    auto contractCallParam2 = Hydra::ContractCallParam();
    contractCallParam2.type = "uint256";
    contractCallParam2.value.push_back(store(446119696266410));

    auto contractCallParam3 = Hydra::ContractCallParam();
    contractCallParam3.type = "address";
    contractCallParam3.value.push_back(AnyAddress::dataFromString("HQMfzgnCPSitwMKFVSnrrdEhNjPXuKV7Hq", TWCoinTypeHydra));

    auto contractCallParam4 = Hydra::ContractCallParam();
    contractCallParam4.type = "uint256";
    contractCallParam4.value.push_back(store(20000000000));

    std::vector<Hydra::ContractCallParam> params = {contractCallParam2, contractCallParam1, contractCallParam3, contractCallParam4};

    auto contractCallInput = buildHydraContractCallInput(250000, 32, "swapExactHYDRAForTokens", params);

    Hydra::SigningInput signingInput;
    signingInput.input = bitcoinSigningInput;
    signingInput.contractCallInput = contractCallInput;

    auto plan = Hydra::TransactionBuilder::plan(signingInput);

    {
        ASSERT_EQ(plan.utxos.size(), 1);
        ASSERT_EQ(hexEncoded(plan.contract.bytes), "0x540390d0034ce4076969f9000000000000000000000000000000000000000000000000000195be5605f4aa0000000000000000000000000000000000000000000000000000000000000080000000000000000000000000c3a87d9b1201a1cba90fba12c315a3d2f25ddc1100000000000000000000000000000000000000000000000000000004a817c8000000000000000000000000000000000000000000000000000000000000000002000000000000000000000000c3a87d9b1201a1cba90fba12c315a3d2f25ddc11000000000000000000000000c3a87d9b1201a1cba90fba12c315a3d2f25ddc11144ab26aaa1803daa638910d71075c06386e391147c2");
    }
}


TEST(Hydra, TestRegularTransactionBuilder){
    
    std::vector<int64_t> amounts = {12545182455, 19152684041};
    auto utxos = buildTestHydraUTXOs(amounts);
    auto bitcoinSigningInput = buildBitcoinSigningInput(1, 3600, utxos, false, TWCoinTypeHydra);

    Hydra::SigningInput signingInput;
    signingInput.input = bitcoinSigningInput;

    auto plan = Hydra::TransactionBuilder::plan(signingInput);

    auto transaction = Hydra::TransactionBuilder::build<Bitcoin::Transaction>(plan, "HGQWcFAkv4WEC5dyknxrv6ZoPhD3rMCRdg", "HGQWcFAkv4WEC5dyknxrv6ZoPhD3rMCRdg", TWCoinTypeHydra,0);
    
    
    {
        ASSERT_EQ(plan.amount, 1);
        ASSERT_EQ(plan.change, 12544368854);
        ASSERT_EQ(plan.fee, 813600);
        ASSERT_EQ(plan.utxos.size(), 1);
        ASSERT_EQ(transaction.outputs.size(), 2);
    }
    
}

TEST(Hydra, TestTokenTransactionBuilder){
    
    std::vector<int64_t> amounts = {12545182455, 19152684041};
    auto utxos = buildTestHydraUTXOs(amounts);
    auto bitcoinSigningInput = buildBitcoinSigningInput(0, 3600, utxos, false, TWCoinTypeHydra, "4ab26aaa1803daa638910d71075c06386e391147");
    auto contractInput = buildHydraContractInput(100000, 32, std::string("HQMfzgnCPSitwMKFVSnrrdEhNjPXuKV7Hq"), 10000000);


    Hydra::SigningInput signingInput;
    signingInput.input = bitcoinSigningInput;
    signingInput.contract = contractInput;

    auto plan = Hydra::TransactionBuilder::plan(signingInput);

    auto transaction = Hydra::TransactionBuilder::build<Bitcoin::Transaction>(plan, "HGQWcFAkv4WEC5dyknxrv6ZoPhD3rMCRdg", "HGQWcFAkv4WEC5dyknxrv6ZoPhD3rMCRdg", TWCoinTypeHydra,0);
    
    {
        ASSERT_EQ(plan.amount, 0);
        ASSERT_EQ(plan.change, 12541168855);
        ASSERT_EQ(plan.fee, 4013600);
        ASSERT_EQ(plan.utxos.size(), 1);
        ASSERT_EQ(transaction.outputs.size(), 2);

    }
}

TEST(Hydra, TestContractCallTransactionBuilder){
    
    std::vector<int64_t> amounts = {12545182455, 19152684041};
    auto utxos = buildTestHydraUTXOs(amounts);
    auto bitcoinSigningInput = buildBitcoinSigningInput(100000, 3600, utxos, false, TWCoinTypeHydra, "4ab26aaa1803daa638910d71075c06386e391147");

   auto contractCallParam1 = Hydra::ContractCallParam();
    contractCallParam1.type = "address[]";
    contractCallParam1.value.push_back(AnyAddress::dataFromString("HQMfzgnCPSitwMKFVSnrrdEhNjPXuKV7Hq", TWCoinTypeHydra));
    contractCallParam1.value.push_back(AnyAddress::dataFromString("HQMfzgnCPSitwMKFVSnrrdEhNjPXuKV7Hq", TWCoinTypeHydra));

    auto contractCallParam2 = Hydra::ContractCallParam();
    contractCallParam2.type = "uint256";
    contractCallParam2.value.push_back(store(446119696266410));

    auto contractCallParam3 = Hydra::ContractCallParam();
    contractCallParam3.type = "address";
    contractCallParam3.value.push_back(AnyAddress::dataFromString("HQMfzgnCPSitwMKFVSnrrdEhNjPXuKV7Hq", TWCoinTypeHydra));

    auto contractCallParam4 = Hydra::ContractCallParam();
    contractCallParam4.type = "uint256";
    contractCallParam4.value.push_back(store(20000000000));

    std::vector<Hydra::ContractCallParam> params = {contractCallParam2, contractCallParam1, contractCallParam3, contractCallParam4};

    auto contractCallInput = buildHydraContractCallInput(250000, 32, "swapExactHYDRAForTokens", params);

    Hydra::SigningInput signingInput;
    signingInput.input = bitcoinSigningInput;
    signingInput.contractCallInput = contractCallInput;


    auto plan = Hydra::TransactionBuilder::plan(signingInput);

    auto transaction = Hydra::TransactionBuilder::build<Bitcoin::Transaction>(plan, "HGQWcFAkv4WEC5dyknxrv6ZoPhD3rMCRdg", "HGQWcFAkv4WEC5dyknxrv6ZoPhD3rMCRdg", TWCoinTypeHydra,0);
    
    {
        ASSERT_EQ(plan.amount, 100000);
        ASSERT_EQ(plan.change, 12536268855);
        ASSERT_EQ(plan.fee, 8813600);
        ASSERT_EQ(plan.utxos.size(), 1);
        ASSERT_EQ(transaction.outputs.size(), 2);

    }
}

TEST(Hydra, TestTransactionSigner){
    std::vector<int64_t> amounts = {12545182455, 19152684041};
    auto utxos = buildTestHydraUTXOs(amounts);
    auto bitcoinSigningInput = buildBitcoinSigningInput(10000000, 3600, utxos, false, TWCoinTypeHydra);

    Hydra::SigningInput signingInput;
    signingInput.input = bitcoinSigningInput;
    

    //Sign
    auto result = Hydra::TransactionSigner::sign(signingInput);
    ASSERT_TRUE(result.isSuccess());
    auto signedTx = result.payload();

    Data serialized;
    signedTx.encode(serialized);
    ASSERT_EQ(hex(serialized),"01000000000101df60e3babacfce81c9efcb268c14a7d33efe567b0000000000000000000000000000000000ffffffff0280969800000000001976a914c3a87d9b1201a1cba90fba12c315a3d2f25ddc1188ac574a1beb0200000016001422e6014ad3631f1939281c3625bc98db808fbfb002483045022100d2ac7dba2aea09eb05839b8f8d8602c7e64b15a5e9dea6c42d87453850f0dca9022026132842c060dadcd6ef9f511ea0336419c0e0b3f487d94a389fac2f02487e540121025cf26d221b01ca4d6040893b96f1dabfd2a108d449b3fa62854421f98a42562b00000000");
}

TEST(Hydra, TestTokenTransactionSigner){
    std::vector<int64_t> amounts = {12545182455, 19152684041};
    auto utxos = buildTestHydraUTXOs(amounts);
    auto bitcoinSigningInput = buildBitcoinSigningInput(0, 3600, utxos, false, TWCoinTypeHydra, "4ab26aaa1803daa638910d71075c06386e391147");
    auto contractInput = buildHydraContractInput(100000, 32, std::string("HQMfzgnCPSitwMKFVSnrrdEhNjPXuKV7Hq"), 10000000);


    Hydra::SigningInput signingInput;
    signingInput.input = bitcoinSigningInput;
    signingInput.contract = contractInput;

    //Sign
    auto result = Hydra::TransactionSigner::sign(signingInput);
    ASSERT_TRUE(result.isSuccess());
    auto signedTx = result.payload();

    Data serialized;
    signedTx.encode(serialized);
    ASSERT_EQ(hex(serialized),"01000000000101df60e3babacfce81c9efcb268c14a7d33efe567b0000000000000000000000000000000000ffffffff02d70c83eb0200000016001422e6014ad3631f1939281c3625bc98db808fbfb00000000000000000605403a0860144a9059cbb000000000000000000000000c3a87d9b1201a1cba90fba12c315a3d2f25ddc110000000000000000000000000000000000000000000000000000000000989680144ab26aaa1803daa638910d71075c06386e391147c202483045022100ab892a7ef616850a912be7d069853935511bd04ff8f7bb335d8cabb76be6f5ed022008bff521185772501d43d80611d03f00a46304b2d99be2cc13b55e1a7f3c3bcf0121025cf26d221b01ca4d6040893b96f1dabfd2a108d449b3fa62854421f98a42562b00000000");
}

