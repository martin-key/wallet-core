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
            checksum: "6364d70104789f8aa339e8224881493388c8d4f78db0bfa4a1d507864b878e3b"
        ),
        .binaryTarget(
            name: "SwiftProtobuf",
            url: "https://github.com/ValeriD/wallet-core-1/releases/download/2.6.38/SwiftProtobuf.xcframework.zip",
            checksum: "0c77d77a9a31b82bed4055cc9f03fb1dd930c23b1f0c8645d9aadb377c300bab"
        )
    ]
)
