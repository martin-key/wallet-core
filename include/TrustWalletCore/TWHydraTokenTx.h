// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "TWBase.h"
#include "TWBitcoinScript.h"
#include "TWData.h"

TW_EXTERN_C_BEGIN

TW_EXPORT_CLASS
struct TWHydraTokenScriptBuilder;

/// Creates an empty script.
TW_EXPORT_STATIC_METHOD
struct TWBitcoinScript *_Nonnull TWHydraTokenScriptBuilderBuildTokenScript(TWData *_Nonnull input);
