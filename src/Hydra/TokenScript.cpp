// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "TokenScript.h"
#include "../Data.h"
#include "OpCodes.h"

#include "../Bitcoin/Script.h"

#include "../Ethereum/RLP.h"
#include "../Ethereum/Transaction.h"

#include "../proto/Hydra.pb.h"

using namespace TW;

Bitcoin::Script Hydra::TokenScript::buildTokenScript(const Data& input){
    
    auto contractInput = Hydra::Proto::ContractInput();
    contractInput.ParseFromArray(input.data(), (int)input.size());
    
    
    
    //Build the transaction
    Data script;
    
    //Append ops_4
    append(script, Ethereum::RLP::encode(TW::Hydra::OpCode::OP_4));
    
    //Append gasLimit
    append(script, Ethereum::RLP::encode(contractInput.gaslimit()));
    
    //Append built function
    append(script, Ethereum::TransactionNonTyped::buildERC20TransferCall(Ethereum::RLP::encode(contractInput.to()), contractInput.amount()));

    //Append contract address
    append(script, Ethereum::RLP::encode(contractInput.contractaddress()));
    
    //Append op_call
    append(script, Ethereum::RLP::encode(TW::Hydra::OpCode::OP_CALL));

    return Bitcoin::Script(script);
    
}
