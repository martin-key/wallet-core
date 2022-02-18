// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.
//
// This is a GENERATED FILE, changes made here MAY BE LOST.
// Generated one-time (codegen/bin/cointests)
//

#include "../interface/TWTestUtilities.h"
#include <TrustWalletCore/TWCoinTypeConfiguration.h>
#include <gtest/gtest.h>


TEST(TWHydraCoinType, TWCoinType) {
    auto symbol = WRAPS(TWCoinTypeConfigurationGetSymbol(TWCoinTypeHydra));
    auto txId = WRAPS(TWStringCreateWithUTF8Bytes("t123"));
    auto txUrl = WRAPS(TWCoinTypeConfigurationGetTransactionURL(TWCoinTypeHydra, txId.get()));
    auto accId = WRAPS(TWStringCreateWithUTF8Bytes("a12"));
    auto accUrl = WRAPS(TWCoinTypeConfigurationGetAccountURL(TWCoinTypeHydra, accId.get()));
    auto id = WRAPS(TWCoinTypeConfigurationGetID(TWCoinTypeHydra));
    auto name = WRAPS(TWCoinTypeConfigurationGetName(TWCoinTypeHydra));

    ASSERT_EQ(TWCoinTypeConfigurationGetDecimals(TWCoinTypeHydra), 8);
    ASSERT_EQ(TWBlockchainBitcoin, TWCoinTypeBlockchain(TWCoinTypeHydra));
    ASSERT_EQ(0x3F, TWCoinTypeP2shPrefix(TWCoinTypeHydra));
    ASSERT_EQ(0x0, TWCoinTypeStaticPrefix(TWCoinTypeHydra));
    assertStringsEqual(symbol, "HYDRA");
    // assertStringsEqual(txUrl, "https://qtum.info/tx/t123");
    // assertStringsEqual(accUrl, "https://qtum.info/address/a12");
    assertStringsEqual(id, "hydra");
    assertStringsEqual(name, "Hydra");
}
