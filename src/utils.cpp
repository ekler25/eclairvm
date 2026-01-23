#include <iostream>
#include <types.hpp>
#include <utils.hpp>

Qword BytesToInt(const Vec<Byte>& Bytes) {
    Qword Value = 0;

    for (Byte B : Bytes) {
        Value = (Value << 8) | B;
    }

    int Bits = Bytes.size() * 8;
    Qword Sign = 1LL << (Bits - 1);

    if (Value & Sign) {
        Value |= (~0LL << Bits);
    }

    return Value;
}

void Err(Error ErrorType, String Value) {
    switch (ErrorType) {
        case Error::File:       std::cout << "[ \x1b[91mFile Error\x1b[0m ] "      << Value << "\n"; break;
        case Error::Fetching:   std::cout << "[ \x1b[91mFetching Error\x1b[0m ] "  << Value << "\n"; break;
        case Error::Decoding:   std::cout << "[ \x1b[91mDecoding Error\x1b[0m ] "  << Value << "\n"; break;
        case Error::Header:     std::cout << "[ \x1b[91mHeader Error\x1b[0m ] "    << Value << "\n"; break;
        case Error::Execution:  std::cout << "[ \x1b[91mRuntime Error\x1b[0m ] "   << Value << "\n"; break;
        case Error::Usage:      std::cout << "[ \x1b[91mUsage Error\x1b[0m ] "     << Value << "\n"; break;
        default:                std::cout << "Unknown error has occured! EVM terminated\n"; break;
    }
    std::exit(1);
}
