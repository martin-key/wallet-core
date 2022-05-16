// swift-tools-version:5.3
import PackageDescription

let package = Package(
    name: "WalletCore",
    platforms: [.iOS(.v13)],
    products: [
        .library(name: "WalletCore", targets: ["WalletCore"]),
        .library(name: "SwiftProtobufWalletCore", targets: ["SwiftProtobufWalletCore"])
    ],
    dependencies: [],
    targets: [
        .binaryTarget(
            name: "WalletCore",
            url: "https://github.com/ValeriD/wallet-core-1/releases/download/2.6.38/WalletCore.xcframework.zip",
            checksum: "ae515d6c2b938fdcbca1acb4d00266e032686eb2ec51a8bffc7d1500c0ed77c3"
        ),
        .binaryTarget(
            name: "SwiftProtobufWalletCore",
            url: "https://github.com/ValeriD/wallet-core-1/releases/download/2.6.38/SwiftProtobufWalletCore.xcframework.zip",
            checksum: "5a2661cdcb630fa2af92f8edd169d92a0be87c69d2eb93a4574fbc797971db6c"
        )
    ]
)
