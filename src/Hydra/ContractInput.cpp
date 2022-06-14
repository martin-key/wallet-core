

#include "ContractInput.h"

TW::Hydra::ContractInput::ContractInput(const Proto::ContractInput& input){
    gasLimit = input.gas_limit();
    gasPrice = input.gas_price();
    to = input.to();
    amount = input.amount();
}