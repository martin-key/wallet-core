// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "TokenScriptBuilder.h"
#include "../Ethereum/RLP.h"
#include "OpCodes.h"
#include "../Ethereum/Transaction.h"

using namespace TW;
using namespace TW::Hydra;

TW::Bitcoin::Script TokenScriptBuilder::buildTokenScript(const ContractInput& input) {
    //Build the transaction
    Data script;
    
    //Append ops_4
    append(script, TW::Ethereum::RLP::encode(TW::Hydra::OpCode::OP_4));
    
    //Append gasLimit
    append(script, TW::Ethereum::RLP::encode(input.gaslimit()));
    
    //Append built function
    append(script, TW::Ethereum::TransactionNonTyped::buildERC20TransferCall(TW::Ethereum::RLP::encode(input.to()), input.amount()));

    //Append contract address
    append(script, TW::Ethereum::RLP::encode(input.contractaddress()));
    
    //Append op_call
    append(script, TW::Ethereum::RLP::encode(TW::Hydra::OpCode::OP_CALL));

    return TW::Bitcoin::Script(script);
}