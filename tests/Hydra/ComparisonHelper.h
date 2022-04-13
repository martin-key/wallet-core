// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include <gtest/gtest.h>
#include "Hydra/TokenScriptBuilder.h"
#include "HexCoding.h"
#include "Bitcoin/Script.h"
#include "Bitcoin/Transaction.h"
#include "Bitcoin/UTXO.h"
#include "Bitcoin/SigningInput.h"

using namespace TW;
Bitcoin::Script buildTokenScript(uint32_t gasLimit, std::string toAddress, uint32_t amount, std::string contractAddress);

/// Build a dummy UTXO with the given amount
Bitcoin::UTXO buildTestHydraUTXO(int64_t amount);

/// Build a set of dummy UTXO with the given amounts
Bitcoin::UTXOs buildTestHydraUTXOs(const std::vector<int64_t>& amounts);

Bitcoin::SigningInput buildHydraSigningInput(Bitcoin::Amount amount, int byteFee, const Bitcoin::UTXOs& utxos, 
bool useMaxAmount = false, enum TWCoinType coin = TWCoinTypeBitcoin);