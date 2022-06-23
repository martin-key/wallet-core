// swift-tools-version:5.3
import PackageDescription

let package = Package(
    name: "WalletCore",
    platforms: [.iOS(.v13)],
    products: [
        .library(name: "WalletCore", targets: ["WalletCore"]),
        .library(name: "SwiftProtobuf", targets: ["SwiftProtobuf"])
    ],
    dependencies: [],
    targets: [
        .binaryTarget(
            name: "WalletCore",
            url: "https://github.com/ValeriD/wallet-core-1/releases/download/2.6.43/WalletCore.xcframework.zip",
            checksum: "c3626db0bd63c302870fa9a14e9f072dacc311e0a95e4b48e3936869d918b59c"
        ),
        .binaryTarget(
            name: "SwiftProtobuf",
            url: "https://github.com/ValeriD/wallet-core-1/releases/download/2.6.43/SwiftProtobuf.xcframework.zip",
            checksum: "cd3733f534bb748b95efcab047be394f120b6c002d196c4e8ce1c1d84330acd3"
        )
    ]
)
