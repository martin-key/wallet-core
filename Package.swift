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
            url: "https://github.com/ValeriD/wallet-core-1/releases/download/2.6.44/WalletCore.xcframework.zip",
            checksum: "7ba614f2de411030e3230cb70519c7efed8045fe6f1767c490e78d2f2d22c38e"
        ),
        .binaryTarget(
            name: "SwiftProtobuf",
            url: "https://github.com/ValeriD/wallet-core-1/releases/download/2.6.44/SwiftProtobuf.xcframework.zip",
            checksum: "26b463905c9c3a003f7c96dec32cbef70aa07ee745b0d9fd59e918428d69fa40"
        )
    ]
)
