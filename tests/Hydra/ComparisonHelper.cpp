// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "ComparisonHelper.h"

#include <TrustWalletCore/TWCoinType.h>

#include "Bitcoin/OutPoint.h"
#include "proto/Bitcoin.pb.h"
#include "proto/Hydra.pb.h"
#include "Data.h"
#include "PrivateKey.h"
#include "HexCoding.h"
#include "BinaryCoding.h"

#include <cassert>
#include <vector>



Bitcoin::Script buildTokenScript(uint32_t gasLimit, std::string toAddress, uint32_t amount, std::string contractAddress){
    auto input = Hydra::Proto::ContractInput();

    input.set_gaslimit(gasLimit);
    input.set_to(toAddress);
    input.set_amount(amount);
    input.set_contractaddress(contractAddress);
    std::string inputAsString = input.SerializeAsString();
    Data inputData =std::vector<byte>(inputAsString.begin(), inputAsString.end());
    return Hydra::TokenScript::buildTokenScript(inputData);

}

auto emptyHydraTxOutPoint = Bitcoin::OutPoint(parse_hex("hc1qytnqzjknvv03jwfgrsmzt0ycmwqgl0asx9rjk6"), 0);

Bitcoin::UTXO buildTestHydraUTXO(int64_t amount) {
    Bitcoin::UTXO utxo;
    utxo.amount = amount;
    utxo.outPoint = emptyHydraTxOutPoint;
    utxo.outPoint.sequence = UINT32_MAX;
    utxo.script = Bitcoin::Script::lockScriptForAddress("hc1qytnqzjknvv03jwfgrsmzt0ycmwqgl0asx9rjk6", TWCoinTypeHydra);
    return utxo;
}

Bitcoin::UTXOs buildTestHydraUTXOs(const std::vector<int64_t>& amounts) {
    Bitcoin::UTXOs utxos;
    for (auto it = amounts.begin(); it != amounts.end(); it++) {
        utxos.push_back(buildTestHydraUTXO(*it));
    }
    return utxos;
}

Bitcoin::SigningInput buildHydraSigningInput(Bitcoin::Amount amount, int byteFee, const Bitcoin::UTXOs& utxos, bool useMaxAmount, enum TWCoinType coin) {
    Bitcoin::SigningInput input;
    input.amount = amount;
    input.byteFee = byteFee;
    input.useMaxAmount = useMaxAmount;
    input.coinType = coin;
    
   
    auto privateKey = TW::PrivateKey(parse_hex("55f9cbb0376c422946fa28397c1219933ac60b312ede41bfacaf701ecd546625"));
    input.privateKeys.push_back(privateKey);

    input.utxos = utxos;
    input.toAddress = "HE4ZCZU2ymUir46JxGjnaauNtkWpmKpCcX";
    input.changeAddress = "hc1qytnqzjknvv03jwfgrsmzt0ycmwqgl0asx9rjk6";
    return input;
}

int64_t sumHydraUTXOs(const Bitcoin::UTXOs& utxos) {
    int64_t s = 0u;
    for (auto& utxo: utxos) {
        s += utxo.amount;
    }
    return s;
}
