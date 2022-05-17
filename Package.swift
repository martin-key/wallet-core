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
            url: "https://github.com/ValeriD/wallet-core-1/releases/download/2.6.38/WalletCore.xcframework.zip",
            checksum: "5e0ce96b1d39855f5b34a75d6810174448f83e6b976e32ceb2f8b62a4db988e5"
        ),
        .binaryTarget(
            name: "SwiftProtobuf",
            url: "https://github.com/ValeriD/wallet-core-1/releases/download/2.6.38/SwiftProtobuf.xcframework.zip",
            checksum: "edc7f4b1c5ee9cc95b98a713b1430f7b9808348ebc9299be784a61821426ada3"
        )
    ]
)
