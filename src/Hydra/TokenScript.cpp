// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include<cmath>
#include <boost/algorithm/string/predicate.hpp>

#include "TokenScript.h"
#include "Data.h"
#include "OpCodes.h"
#include "HexCoding.h"
#include "AnyAddress.h"
#include "BinaryCoding.h"
#include "../Bitcoin/Script.h"
#include "../Ethereum/RLP.h"
#include "../Ethereum/ABI.h"
#include "../Ethereum/Transaction.h"
#include "../uint256.h"

#include "../proto/Hydra.pb.h"

using namespace TW;
using namespace boost::algorithm;

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

bool isArrayType(const std::string& type) {
    return ends_with(type, "[]") && type.length() >= 3;
}

std::string getArrayElemType(const std::string& arrayType) {
    if (isArrayType(arrayType)) {
        return arrayType.substr(0, arrayType.length() - 2);
    }
    return "";
}


void insert(Data& script, Data& input){
    if(input.size() < Hydra::OpCode::OP_PUSHDATA1){
        script.push_back(static_cast<byte>(input.size()));
    } else if (input.size() <= 0xff){
        append(script, Hydra::OpCode::OP_PUSHDATA1);
        script.push_back(static_cast<byte>(input.size()));
    } else if(input.size() <= 0xffff){
        append(script, Hydra::OpCode::OP_PUSHDATA2);

        Data tmp;
        uint16_t size = static_cast<uint16_t>(input.size());
        encode16LE(size, tmp);

        append(script, tmp);

    }else {
        append(script, Hydra::OpCode::OP_PUSHDATA4);

        Data tmp;
        uint32_t size = static_cast<uint32_t>(input.size());

        encode32LE(size,tmp);

        append(script, tmp);
    }

    append(script, input);
}

Bitcoin::Script Hydra::TokenScript::buildTokenScript(int64_t gasLimit, const std::string& to, uint64_t amount, const std::string& contractAddress){
    
    //Build the transaction
    Data script;
    
    //Append op_4
    append(script, Hydra::OpCode::OP_4);
    
    //Convert the gas limit to hex
    Data gasLimitData = numberToBuffer(gasLimit);


    //Insert the gas limit data
    insert(script, gasLimitData);

    // Building the transfer function
    Data data = Ethereum::TransactionNonTyped::buildERC20TransferCall(AnyAddress::dataFromString(to,TWCoinTypeHydra), amount);

    //Insert the encoded data
    insert(script, data);
    
    //Convertiung the contract address to data
    Data contractAddressData = parse_hex(contractAddress);

    //Insert contract address
    insert(script, contractAddressData);
    
    //Append op_call
    append(script, TW::Hydra::OpCode::OP_CALL);

    return Bitcoin::Script(script);
}

TW::Bitcoin::Script Hydra::TokenScript::buildContractCallScript(int64_t gasLimit, const std::string& function, std::vector<ContractCallParam>& params, const std::string contractAddress){
    
    Data script;

    append(script, Hydra::OpCode::OP_4);

    Data gasLimitData = numberToBuffer(gasLimit);

    insert(script, gasLimitData);

    // Function building must be in separate function
    std::vector<std::shared_ptr<Ethereum::ABI::ParamBase>> parameters;
    for(auto& param: params){ 
       auto abiParam = Ethereum::ABI::ParamFactory::make(param.type);
        
        if(isArrayType(param.type)){  //Check if the type is array
            std::vector<std::shared_ptr<Ethereum::ABI::ParamBase>> vectorParams;
            for(auto& paramValue : param.value){ // Iterate through every data in value
                auto p = Ethereum::ABI::ParamFactory::make(getArrayElemType(param.type)); // Create new param of the required type
                p->setValueJson(hexEncoded(paramValue)); // Set value to the param
                vectorParams.push_back(p);
            }
            auto arr = make_shared<Ethereum::ABI::ParamArray>(vectorParams);  // Cast the parameter to type Array

            abiParam = arr;
        }else{
            abiParam->setValueJson(hexEncoded(param.value[0]));     
        }
        parameters.push_back(abiParam);
    }
    
    auto f = Ethereum::ABI::Function(function, parameters);

    Data payload;
    f.encode(payload);

    insert(script, payload);
    
    // Insert the contract address as data
    Data contractAddressData = parse_hex(contractAddress);
    insert(script, contractAddressData);

    // Append the op code
    append(script, Hydra::OpCode::OP_CALL);

    return Bitcoin::Script(script);
}

