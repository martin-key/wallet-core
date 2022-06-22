#include "ContractCallInput.h"

using namespace TW;
using namespace Hydra;

ContractCallParam::ContractCallParam(const Proto::ContractCallParam& param)
    : type(param.type())
{
    for (auto& v: param.value()){
        value.push_back(Data(v.begin(), v.end()));
    }
}

ContractCallInput::ContractCallInput(const Proto::ContractCallInput& input){
    gasLimit = input.gas_limit();
    gasPrice = input.gas_price();

    functionName = input.function_name();

    for(auto& p: input.parameters()){
        parameters.push_back(ContractCallParam(p));
    }
}