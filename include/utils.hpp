#include <types.hpp>

static constexpr Byte EVMVersion = 0x00;

enum class InvokeHost {
    Terminate,
    StdOut,
    StdIn,
};

enum class Error {
    File, Fetching, Decoding, Header, Execution, Usage
};

Qword BytesToInt(const Vec<Byte>& Bytes);
void Err(Error ErrorType, String Value);
