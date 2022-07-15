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
            url: "https://github.com/ValeriD/wallet-core-1/releases/download/2.6.45/WalletCore.xcframework.zip",
            checksum: "d988a7b6cdd194d591e40e3e92e7e2cea54f2e91392162c19529d6233eb371b8"
        ),
        .binaryTarget(
            name: "SwiftProtobuf",
            url: "https://github.com/ValeriD/wallet-core-1/releases/download/2.6.45/SwiftProtobuf.xcframework.zip",
            checksum: "bb177f8fc831f451d83f8a73d76baedc9072720fbfe9e948f210f94c8b9551e6"
        )
    ]
)
