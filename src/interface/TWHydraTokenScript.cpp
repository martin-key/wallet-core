//
//  TWHydraTokenScriptBuilder.cpp
//  
//
//  Created by GoStartups Service on 27.05.22.
//

#include <TrustWalletCore/TWHydraTokenScript.h>
#include "../Hydra/TokenScript.h"
#include <iterator>


using namespace TW;

struct TWBitcoinScript *_Nonnull TWHydraTokenScriptBuildTokenScript(TWData *_Nonnull input){
    auto* s = reinterpret_cast<const std::vector<uint8_t>*>(input);
    auto script = Hydra::TokenScript::buildTokenScript(*s);
    return new TWBitcoinScript{ .impl = script };
}
