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
            url: "https://github.com/ValeriD/wallet-core-1/releases/download/2.6.37/WalletCore.xcframework.zip",
            checksum: "60bf95a8bf265fa34a2aa52c7768fb3df1cb08c43aef9a81d4cef31c32cdbd61"
        ),
        .binaryTarget(
            name: "SwiftProtobuf",
            url: "https://github.com/ValeriD/wallet-core-1/releases/download/2.6.37/SwiftProtobuf.xcframework.zip",
            checksum: "aba1c7639f39d76caaa40ae997d5b488053f0b3f6c7cc1eb4e85a9d4429e79dc"
        )
    ]
)
