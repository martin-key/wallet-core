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
#include<map>
#include "Bitcoin/TransactionInput.h"
#include "Bitcoin/Transaction.h"
#include "Bitcoin/SigningInput.h"
#include "Data.h"
#include "PrivateKey.h"
#include "Hydra/TransactionBuilder.h"


using namespace TW;
TEST(Hydra, ContractTokenScript){

    auto res = buildTokenScript(1000, "HPjtxTZwy8i4emXxb64hz82x3s6q48LbGz", 10, "4ab26aaa1803daa638910d71075c06386e391147");

    std::string expected = "0x548203e8a9059cbb0000000000000000000000005878623634687a3832783373367134384c62477a000000000000000000000000000000000000000000000000000000000000000aa83461623236616161313830336461613633383931306437313037356330363338366533393131343781c2";

    {
        ASSERT_EQ(hexEncoded(res.bytes), expected);
    }
}

TEST(Hydra, TestTransactionBuilder){
    auto po0 = TW::Bitcoin::OutPoint(parse_hex("94be46260220bce2872e3ad69f4b7828792a3db0a6f460a8e956d6ea379b011d"), 1);
    auto po1 = TW::Bitcoin::OutPoint(parse_hex("7435b2e54bc8e1b0312cc721aaa321df3db59ea721db13188abb8787c1c30257"), 1);
    
    auto privateKey = TW::PrivateKey(parse_hex("7fdafb9db5bc501f2096e7d13d331dc7a75d9594af3d251313ba8b6200f4e384"));
    
    Bitcoin::UTXOs utxos;
    Bitcoin::UTXO utxo0;
    Bitcoin::UTXO utxo1;
    utxo0.outPoint = po0;
    utxo0.script = Bitcoin::Script();
    utxo0.amount = 12545182455;

    utxo1.outPoint = po1;
    utxo1.script = Bitcoin::Script();
    utxo1.amount = 19152684041;
    utxos.push_back(utxo0);
    utxos.push_back(utxo1); 

    Bitcoin::SigningInput input;
    input.amount = 10000000000;
    input.changeAddress = "HGQWcFAkv4WEC5dyknxrv6ZoPhD3rMCRdg";
    input.coinType = TWCoinTypeHydra;
    input.toAddress = "HGQWcFAkv4WEC5dyknxrv6ZoPhD3rMCRdg";
    input.hashType = TWBitcoinSigHashTypeAll;
    input.byteFee = 3600;
    input.utxos = utxos;
    input.privateKeys = std::vector<TW::PrivateKey>({privateKey});

    // std::map<std::string, Bitcoin::Script> scripts = {{"contract", buildTokenScript(1000, "HPjtxTZwy8i4emXxb64hz82x3s6q48LbGz", 10, "4ab26aaa1803daa638910d71075c06386e391147")}};
    // input.scripts = scripts;

    auto plan = Hydra::TransactionBuilder::plan(input);

    auto transaction = Hydra::TransactionBuilder::build<Bitcoin::Transaction>(plan, "HFsP8t3JwkUUUiqijMfGnWwtxc8wNvL92b", "HFsP8t3JwkUUUiqijMfGnWwtxc8wNvL92a", TWCoinTypeHydra,0);
    
    
    {
        ASSERT_EQ(plan.amount, 10000000000);
        ASSERT_EQ(plan.change, 9151870441);
        ASSERT_EQ(plan.fee, 813600);
        ASSERT_EQ(plan.utxos.size(), 1);
        ASSERT_EQ(transaction.outputs.size(), 3);

    }
    
}

