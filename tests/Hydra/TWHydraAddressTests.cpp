// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "../interface/TWTestUtilities.h"

#include <TrustWalletCore/TWSegwitAddress.h>
#include <TrustWalletCore/TWBitcoinAddress.h>
#include <TrustWalletCore/TWBitcoinScript.h>
#include <TrustWalletCore/TWHash.h>
#include <TrustWalletCore/TWHDWallet.h>
#include <TrustWalletCore/TWHRP.h>
#include <TrustWalletCore/TWPrivateKey.h>

#include <gtest/gtest.h>

TEST(Hydra, LegacyAddress) {
    auto privateKey = WRAP(TWPrivateKey, TWPrivateKeyCreateWithData(DATA("a22ddec5c567b4488bb00f69b6146c50da2ee883e2c096db098726394d585730").get()));
    auto publicKey = WRAP(TWPublicKey, TWPrivateKeyGetPublicKeySecp256k1(privateKey.get(), true));
    auto address = WRAP(TWBitcoinAddress, TWBitcoinAddressCreateWithPublicKey(publicKey.get(), TWCoinTypeP2pkhPrefix(TWCoinTypeHydra)));
    auto addressString = WRAPS(TWBitcoinAddressDescription(address.get()));
    assertStringsEqual(addressString, "HGQWcFAkv4WEC5dyknxrv6ZoPhD3rMCRdg");
}

TEST(Hydra, Address) {
    auto privateKey = WRAP(TWPrivateKey, TWPrivateKeyCreateWithData(DATA("55f9cbb0376c422946fa28397c1219933ac60b312ede41bfacaf701ecd546625").get()));
    auto publicKey = WRAP(TWPublicKey, TWPrivateKeyGetPublicKeySecp256k1(privateKey.get(), true));
    auto address = WRAP(TWSegwitAddress, TWSegwitAddressCreateWithPublicKey(TWHRPHydra, publicKey.get()));
    auto string = WRAPS(TWSegwitAddressDescription(address.get()));

    assertStringsEqual(string, "hc1qytnqzjknvv03jwfgrsmzt0ycmwqgl0asx9rjk6");
}

TEST(Hydra, LockScripts) {
    auto script = WRAP(TWBitcoinScript, TWBitcoinScriptLockScriptForAddress(STRING("Sbz3t2RDiK5dqHwNceTwTPPCuYuwr8tQiS").get(), TWCoinTypeHydra));
    auto scriptData = WRAPD(TWBitcoinScriptData(script.get()));
    assertHexEqual(scriptData, "a914a124c6de21e9dd5cc9b3f6730c4fd3f6ec02d01087");

    auto script2 = WRAP(TWBitcoinScript, TWBitcoinScriptLockScriptForAddress(STRING("HEif5mEvYidZX5tLG8puF1iJ8jtVeELrD9").get(), TWCoinTypeHydra));
    auto scriptData2 = WRAPD(TWBitcoinScriptData(script2.get()));
    assertHexEqual(scriptData2, "76a91459ef34d1432a935e5f5664a4fe3b32287327fa1688ac");

    auto script3 = WRAP(TWBitcoinScript, TWBitcoinScriptLockScriptForAddress(STRING("hc1qtgepxtmald9yru05xe4l8hku7d0fpps7pcd522").get(), TWCoinTypeHydra));
    auto scriptData3 = WRAPD(TWBitcoinScriptData(script3.get()));
    assertHexEqual(scriptData3, "00145a32132f7dfb4a41f1f4366bf3dedcf35e90861e");
}

TEST(Hydra, ExtendedKeys) {
    auto wallet = WRAP(TWHDWallet, TWHDWalletCreateWithMnemonic(
        STRING("ripple scissors kick mammal hire column oak again sun offer wealth tomorrow wagon turn fatal").get(),
        STRING("TREZOR").get()
    ));

    // .bip44
    auto xprv = WRAPS(TWHDWalletGetExtendedPrivateKey(wallet.get(), TWPurposeBIP44, TWCoinTypeHydra, TWHDVersionXPRV));
    auto xpub = WRAPS(TWHDWalletGetExtendedPublicKey(wallet.get(), TWPurposeBIP44, TWCoinTypeHydra, TWHDVersionXPUB));

    assertStringsEqual(xprv, "xprv9xrufnFb23jA5RZCgkKNNMtpQKqjHcNkMa1rs21VF3jUdiHKMt6vYKeTdjzf97jpRcsunaxqcNF8vrhaX5UoJMrZyjHnGkq2JagfoY9M4RX");
    assertStringsEqual(xpub, "xpub6BrG5HnUrRHTHudfnmrNjVqYxMgDh56binwTfQR6oPGTWWcTuRRB67xwUztFRj1FiZY79JhypFsvAaZHVJJ7ZUJWLdRLyVFpLYMkAnroGmg");

    // .bip49
    auto yprv = WRAPS(TWHDWalletGetExtendedPrivateKey(wallet.get(), TWPurposeBIP49, TWCoinTypeHydra, TWHDVersionYPRV));
    auto ypub = WRAPS(TWHDWalletGetExtendedPublicKey(wallet.get(), TWPurposeBIP49, TWCoinTypeHydra, TWHDVersionYPUB));

    assertStringsEqual(yprv, "yprvAJhRT6h6eD5zXshKGBffT4mdxstgz5LCC1PAKcP7WaknfXKqfX6jbpeApiQE43tktQRw365gyy4PgAVs7YnuQqF2r9fxas6i5yExjMBssag");
    assertStringsEqual(ypub, "ypub6XgmrcDzUaeHkMmnNDCfpCiNWujBPY43ZEJm7znj4vHmYKezD4Qz9cxefww85Bn8EFpGwnZbUxN2VFnemXPDkUEdqNufUWBcJv1jyjCD1wd");

    // .bip84
    auto zprv = WRAPS(TWHDWalletGetExtendedPrivateKey(wallet.get(), TWPurposeBIP84, TWCoinTypeHydra, TWHDVersionZPRV));
    auto zpub = WRAPS(TWHDWalletGetExtendedPublicKey(wallet.get(), TWPurposeBIP84, TWCoinTypeHydra, TWHDVersionZPUB));
    assertStringsEqual(zprv, "zprvAcmYNTNwajvHP2LmGHNkCaCrtuPcaeAR1VRuu5Q13Q7C5A1Y1jgsazYYuMCk3oGQ4Zkvrdac9WUYTiszrxFNmPGe8Y82itjdjodhG7KNAEY");
    assertStringsEqual(zpub, "zpub6qktmxuqR7UabWRENJukZi9bSwE6z6tGNiMWhTocbjeAwxLgZH188ns2kckkyyr7DuJmbFaxG252eseyVEZwcRUBapx5McZQfo9TFB23xC1");
}

TEST(Hydra, DeriveFromXpub) {
    auto xpub = STRING("xpub6CAkJZPecMDxRXEXZpDwyxcQ6CGie8GdovuJhsGwc2gFbLxdGr1PyqBXmsL7aYds1wfY2rB3YMVZiEE3CB3Lkj6KGoq1rEJ1wuaGkMDBf1m");
    auto pubKey2 = WRAP(TWPublicKey, TWHDWalletGetPublicKeyFromExtended(xpub.get(), TWCoinTypeHydra, STRING("m/44'/609'/0'/0/2").get()));
    auto pubKey9 = WRAP(TWPublicKey, TWHDWalletGetPublicKeyFromExtended(xpub.get(), TWCoinTypeHydra, STRING("m/44'/609'/0'/0/9").get()));

    auto address2 = WRAP(TWBitcoinAddress, TWBitcoinAddressCreateWithPublicKey(pubKey2.get(), TWCoinTypeP2pkhPrefix(TWCoinTypeHydra)));
    auto address2String = WRAPS(TWBitcoinAddressDescription(address2.get()));

    auto address9 = WRAP(TWBitcoinAddress, TWBitcoinAddressCreateWithPublicKey(pubKey9.get(), TWCoinTypeP2pkhPrefix(TWCoinTypeHydra)));
    auto address9String = WRAPS(TWBitcoinAddressDescription(address9.get()));

    assertStringsEqual(address2String, "HCogvCoUwHzC9MgS6bzAx2KfRzxuCpmj8t");
    assertStringsEqual(address9String, "HRWTXFLUvhg6Lh1shdzqm3nozrSbJAAJcL");
}

TEST(Hydra, DeriveFromZpub) {
    auto zpub = STRING("zpub6rJJqJZcpaC7DrdsYiprLfUfvtaf11ZZWmrmYeWMkdZTx6tgfQLiBZuisraogskwBRLMGWfXoCyWRrXSypwPdNV2UWJXm5bDVQvBXvrzz9d");
    auto pubKey4 = WRAP(TWPublicKey, TWHDWalletGetPublicKeyFromExtended(zpub.get(), TWCoinTypeHydra, STRING("m/44'/609'/0'/0/4").get()));
    auto pubKey11 = WRAP(TWPublicKey, TWHDWalletGetPublicKeyFromExtended(zpub.get(), TWCoinTypeHydra, STRING("m/44'/609'/0'/0/11").get()));

    auto address4 = WRAP(TWSegwitAddress, TWSegwitAddressCreateWithPublicKey(TWHRPHydra, pubKey4.get()));
    auto address4String = WRAPS(TWSegwitAddressDescription(address4.get()));

    auto address11 = WRAP(TWSegwitAddress, TWSegwitAddressCreateWithPublicKey(TWHRPHydra, pubKey11.get()));
    auto address11String = WRAPS(TWSegwitAddressDescription(address11.get()));

    assertStringsEqual(address4String, "hc1q3cvjmc2cgjkz9y58waj3r9ccchmrmrdzukkz8a");
    assertStringsEqual(address11String, "hc1qrlk0ajg6khu2unsdppggs3pgpxxvdeym2anma9");
}

/*
HD scheme that is used in Hydra desktop wallet is "<MASTER KEY>/<COIN>/<INTERNAL>":
m/88'/0'
m/88'/1'
The trust wallet use different approach "<MASTER KEY>/<PURPOSE>/<COIN>":
m/44'/609'
m/49'/609'
m/84'/609'
The master key is used to derive the other keys, so the wallet should work but will not be compatible with Hydra desktop wallet.
The rules for creating send/receive Hydra transactions are the same as Bitcoin.
The default addresses in Hydra are the legacy addresses.
*/
