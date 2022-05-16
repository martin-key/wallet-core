// swift-tools-version:5.3
import PackageDescription

let package = Package(
    name: "WalletCore",
    platforms: [.iOS(.v13)],
    products: [
        .library(name: "WalletCore", targets: ["WalletCore"]),
        .library(name: "SwiftProtobufWalletCore", targets: ["SwiftProtobuf"])
    ],
    dependencies: [],
    targets: [
        .binaryTarget(
            name: "WalletCore",
            url: "https://github.com/ValeriD/wallet-core-1/releases/download/2.6.38/WalletCore.xcframework.zip",
            checksum: "9f0760b5b7c7d4bb9a82b0f5a2e1c6f02e33da56c9e4ea281a906848fd738fc1"
        ),
        .binaryTarget(
            name: "SwiftProtobuf",
            url: "https://github.com/ValeriD/wallet-core-1/releases/download/2.6.38/SwiftProtobuf.xcframework.zip",
            checksum: "30a654666cb4956ae5594a1ab6dc6fa151255431a2d3ecfd464786d4a2484635"
        )
    ]
)
