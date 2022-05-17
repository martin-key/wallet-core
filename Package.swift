// swift-tools-version:5.3
import PackageDescription

let package = Package(
    name: "WalletCore",
    platforms: [.iOS(.v13)],
    products: [
        .library(name: "WalletCore", targets: ["WalletCore"])
    ],
    dependencies: [
        .package(
              name: "SwiftProtobuf",
              url: "https://github.com/apple/swift-protobuf.git",
              "1.19.0" ..< "2.0.0"
            )
    ],
    targets: [
        .binaryTarget(
            name: "WalletCore",
            url: "https://github.com/ValeriD/wallet-core-1/releases/download/2.6.39/WalletCore.xcframework.zip",
            checksum: "4a79312747c64edde6191712c67d91d2fd9323f18b66115d487173f600041e43"
        ),
        
    ]
)
