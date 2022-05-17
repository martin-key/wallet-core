// swift-tools-version:5.3
import PackageDescription

let package = Package(
    name: "WalletCore",
    platforms: [.iOS(.v13)],
    products: [
        .library(name: "WalletCore", targets: ["WalletCore", "SwiftProtobuf"]),
    ],
    dependencies: [],
    targets: [
        .binaryTarget(
            name: "WalletCore",
            url: "https://github.com/ValeriD/wallet-core-1/releases/download/2.6.39/WalletCore.xcframework.zip",
            checksum: "4a79312747c64edde6191712c67d91d2fd9323f18b66115d487173f600041e43"
        ),
        .binaryTarget(
            name: "SwiftProtobuf",
            url: "https://github.com/ValeriD/wallet-core-1/releases/download/2.6.39/SwiftProtobuf.xcframework.zip",
            checksum: "7072a8af78f0dac3228ddb71c7f312128a209c0ce4962817943702291436a5e1"
        )
    ]
)
