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
            url: "https://github.com/ValeriD/wallet-core-1/releases/download/2.6.42/WalletCore.xcframework.zip",
            checksum: "6a6c7c5f3422b6d225a067ad90f06c9fd701a488b92d95f21f6e3b32af431b4c"
        ),
        .binaryTarget(
            name: "SwiftProtobuf",
            url: "https://github.com/ValeriD/wallet-core-1/releases/download/2.6.42/SwiftProtobuf.xcframework.zip",
            checksum: "9ed5408667c3600bdc26ac7a0d189305fd2c013193ee4c9a53cd3ea95772dd24"
        )
    ]
)
