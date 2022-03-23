// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "TokenScriptBuilder.h"
#include "../Ethereum/RLP.h"
#include "./Opcodes.h"


TW::Bitcoin::Script TokenScriptBuilder::buildTokenScript(const ContractInput& input) const{
    //Build the transaction
    Data script;
    
    //Append ops_4
    append(script, TW::Ethereum::RLP::encode(OpCode::OP_4));
    
    //Append gasLimit
    append(script, TW::Ethereum::RLP::encode(input.gasLimit));
    
    //Append built function
    append(script, TW::Ethereum::buildERC20TransferCall(input.to, input.amount));

    //Append contract address
    append(script, TW::Ethereum::RLP::encode(input.contractAddress));
    
    //Append op_call
    append(script, TW::Ethereum::RLP::encode(OpCode::OP_CALL));

    return TW::Bitcoin::Script(script);
}