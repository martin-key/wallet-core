// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include<cmath>

#include "TokenScript.h"
#include "../Data.h"
#include "OpCodes.h"
#include "HexCoding.h"
#include "AnyAddress.h"

#include "../Bitcoin/Script.h"

#include "../Ethereum/RLP.h"
#include "../Ethereum/Transaction.h"

#include "../proto/Hydra.pb.h"

using namespace TW;

Data numberToBuffer(int64_t num){
    Data data;
    bool neg = (num<0);
    num = std::abs(num);
    while(num){
        data.push_back(num & 0xff);
        num = num >> 8;
    }
    auto top = data[data.size()-1];
    if(top & 0x80){
        data[data.size()] = neg ? 0x80: 0x00;
    }
    else if(neg){
        data[data.size()] = top | 0x80;
    }
    
    return data;
}


Bitcoin::Script Hydra::TokenScript::buildTokenScript(int64_t gasLimit, const std::string& to, uint64_t amount, const std::string& contractAddress){
    
    // auto contractInput = Hydra::Proto::ContractInput();
    // contractInput.ParseFromArray(input.data(), (int)input.size());
    
    //Build the transaction
    Data script;
    
    //
    append(script, parse_hex("010403"));
    
    //Append gasLimit
    append(script, numberToBuffer(gasLimit));
    
    //Separator
    append(script, parse_hex("44"));
    
    //Append built function
    append(script, Ethereum::TransactionNonTyped::buildERC20TransferCall(AnyAddress::dataFromString(to,TWCoinTypeHydra), amount));

    //Separator
    append(script, parse_hex("14"));
    
    //Append contract address
    append(script, parse_hex(contractAddress));
    
    //Append op_call
    append(script, TW::Hydra::OpCode::OP_CALL);

    return Bitcoin::Script(script);
     
    
}

