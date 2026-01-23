#include <iostream>
#include <classes/machine.hpp>
#include <classes/value.hpp>
#include <types.hpp>
#include <utils.hpp>

void Machine::JMP(Vec<Byte>& Operands) {
    IP = Operands[0];
}

void Machine::IPUSH(Vec<Byte>& Operands) {
    if (Operands.empty())
        throw RuntimeError("[ \x1b[91mRuntime Error\x1b[0m ] Failed to execute ipush : no value provieded!\n");

    Value Val;
    Val.InitInt(BytesToInt(Operands));

    OperandStack.push_back(Val);
}

void Machine::CALL(Vec<Byte>& Operands) {
    if (Operands.empty())
        Err(Error::Execution, "Function identifier not specified");

    Function& Fn = GlobalFunctionTable[Operands[0]];

    if (OperandStack.size() < Fn.Args)
        Err(Error::Execution, "Not enough arguments for function call");

    uint32 VarPtr = OperandStack.size() - Fn.Args;

    OperandStack.resize(VarPtr + Fn.Args + Fn.Locals);

    CallStack.emplace_back(
        IP + 1,
        VarPtr,
        Fn.Args + Fn.Locals 
    );

    IP = Fn.Address;
}

void Machine::RET(Vec<Byte>& Operands) {
    if (CallStack.empty())
        Err(Error::Execution, "RET cannot be executed on an empty callstack");

    CallStackFrame& Frame = CallStack.back();

    OperandStack.resize(Frame.VarPtr);

    IP = Frame.ReturnAddress;
    CallStack.pop_back();
}

void Machine::INVH(Vec<Byte>& Operands) {
    switch (Operands[0]) {
        case 0: std::exit(0);
        case 1:
            if (OperandStack.size() > 0) {
                Value Output = OperandStack.back();
                if (Output.Type == ValueType::Char) std::cout << Output.c;
                if (Output.Type == ValueType::Str) std::cout << Output.s;
                if (Output.Type == ValueType::Int32) std::cout << Output.i;
                OperandStack.pop_back();
            }
            break;
        case 3: std::cout << "\n"; break;
        case 255: std::exit(1);
        default: break;
    }
}

void Machine::EOP(Vec<Byte>& Operands) {

}

void Machine::IPOP(Vec<Byte>& Operands) {

}

void Machine::IADD(Vec<Byte>& Operands) {
    if (OperandStack.size() < 2) return;
    Value Lhs = OperandStack.back();
    OperandStack.pop_back();

    Value Rhs = OperandStack.back();
    OperandStack.pop_back();

    if (!(Rhs.Type == ValueType::Int32 && Lhs.Type == ValueType::Int32)) return;

    Value Val;
    Val.InitInt(Lhs.i + Rhs.i);

    OperandStack.push_back(Val);
}

void Machine::ISUB(Vec<Byte>& Operands) {
    if (OperandStack.size() < 2) return;
    Value Lhs = OperandStack.back();
    OperandStack.pop_back();

    Value Rhs = OperandStack.back();
    OperandStack.pop_back();

    if (!(Rhs.Type == ValueType::Int32 && Lhs.Type == ValueType::Int32)) return;

    Value Val;
    Val.InitInt(Lhs.i - Rhs.i);

    OperandStack.push_back(Val);
}

void Machine::IMUL(Vec<Byte>& Operands) {
    if (OperandStack.size() < 2) return;
    Value Lhs = OperandStack.back();
    OperandStack.pop_back();

    Value Rhs = OperandStack.back();
    OperandStack.pop_back();

    if (!(Rhs.Type == ValueType::Int32 && Lhs.Type == ValueType::Int32)) return;

    Value Val;
    Val.InitInt(Lhs.i * Rhs.i);

    OperandStack.push_back(Val);
}

void Machine::IDIV(Vec<Byte>& Operands) {
    if (OperandStack.size() < 2) return;
    Value Lhs = OperandStack.back();
    OperandStack.pop_back();

    Value Rhs = OperandStack.back();
    OperandStack.pop_back();

    if (!(Rhs.Type == ValueType::Int32 && Lhs.Type == ValueType::Int32)) return;

    Value Val;
    Val.InitInt(Lhs.i / Rhs.i);

    OperandStack.push_back(Val);
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

void Machine::STOREG(Vec<Byte>& Operands) {
    if (OperandStack.size() < 1) return;
    if (Operands.empty())
        throw RuntimeError("[\x1b[91mRuntime Error\x1b[0m] Failed to execute storeg : no index provided!\n");

    if (GlobalVariableTable.size() <= BytesToInt(Operands))
        GlobalVariableTable.resize(BytesToInt(Operands) + 1); 

    Value Val = OperandStack.back();
    OperandStack.pop_back();

    GlobalVariableTable[BytesToInt(Operands)] = Val;
}

void Machine::STOREL(Vec<Byte>& Operands) {

}

void Machine::LOADG(Vec<Byte>& Operands) {
    if (Operands.empty())
        throw RuntimeError("[\x1b[91mRuntime Error\x1b[0m] Failed to execute loadg : no index provided!\n");

    if (GlobalVariableTable.size() <= BytesToInt(Operands))
        throw RuntimeError("[\x1b[91mRuntime Error\x1b[0m] Failed to execute loadg : invalid index!\n");

    Value Val = GlobalVariableTable[BytesToInt(Operands)];

    OperandStack.push_back(Val);
}

void Machine::LOADL(Vec<Byte>& Operands) {

}
