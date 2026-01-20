#include <types.hpp>

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
