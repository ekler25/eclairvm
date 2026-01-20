#include <types.hpp>

enum class InvokeHost {
    Terminate,
    StdOut,
    StdIn,
};

Qword BytesToInt(const Vec<Byte>& Bytes);
