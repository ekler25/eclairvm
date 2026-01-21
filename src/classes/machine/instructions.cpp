#include <iostream>
#include <classes/machine.hpp>
#include <classes/value.hpp>
#include <types.hpp>
#include <utils.hpp>

void Machine::JMP(Vec<Byte>& Operands) {
    IP += Operands[0];
}

void Machine::IPUSH(Vec<Byte>& Operands) {
    if (Operands.empty())
        throw RuntimeError("[ \x1b[91mRuntime Error\x1b[0m ] Failed to execute ipush : no value provieded!\n");

    Value Val;
    Val.InitInt(BytesToInt(Operands));

    OperandStack.push_back(Val);
}

void Machine::CALL(Vec<Byte>& Operands) {

}

void Machine::RET(Vec<Byte>& Operands) {

}

void Machine::INVH(Vec<Byte>& Operands) {
    switch (Operands[0]) {
        case 0: return;
        case 1:
            if (OperandStack.size() > 0) {
                Value Output = OperandStack.back();
                if (Output.Type == ValueType::Char) std::cout << Output.c;
                if (Output.Type == ValueType::Str) std::cout << Output.s;
                if (Output.Type == ValueType::Int) std::cout << Output.i;
                OperandStack.pop_back();
            }
            break;
        default: break;
    }
}

void Machine::EOP(Vec<Byte>& Operands) {

}

void Machine::IPOP(Vec<Byte>& Operands) {

}

void Machine::IADD(Vec<Byte>& Operands) {

}

void Machine::ISUB(Vec<Byte>& Operands) {

}

void Machine::IMUL(Vec<Byte>& Operands) {

}

void Machine::IDIV(Vec<Byte>& Operands) {

}

void Machine::CPUSH(Vec<Byte>& Operands) {
    if (Operands.empty())
        throw RuntimeError("[\x1b[91mRuntime Error\x1b[0m] Failed to execute cpush : no value provided!\n");

    Value Val;
    Val.InitChar((char)Operands[0]);

    OperandStack.push_back(Val);
}

void Machine::SPUSH(Vec<Byte>& Operands) {
    if (Operands.empty())
        throw RuntimeError("[\x1b[91mRuntime Error\x1b[0m] Failed to execute cpush : no value provided!\n");

    Value Val;
    String Str;
    for (int i = 0; i < Operands.size(); i++) {
        Str += Operands[i];
    }
    Val.InitStr(Str);

    OperandStack.push_back(Val);
}
