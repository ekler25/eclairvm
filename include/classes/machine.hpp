#pragma once

#include <classes/frame.hpp>
#include <classes/value.hpp>
#include <classes/instruction.hpp>
#include <types.hpp>

struct Machine {
    Vec<Value>    GlobalVariableTable;
    Vec<Function> GlobalFunctionTable;
    
    Vec<CallStackFrame> CallStack;
    Vec<Value>          OperandStack;
    Vec<UPtr<String>>   StringHeap;

    int64 IP = 0;
    int16 FunctionCount = 0x0000;
    int8  Flags = 0x00;
    int8  Version = 0x00;
    
    Vec<Instruction> Decode(Vec<Byte>& Bytecode);
    void Execute(Vec<Instruction> Inst);

    void JMP(Vec<Byte>& Operands);
    void CALL(Vec<Byte>& Operands);
    void RET(Vec<Byte>& Operands);
    void INVH(Vec<Byte>& Operands);
    void EOP(Vec<Byte>& Operands);
    void IPOP(Vec<Byte>& Operands);
    void IADD(Vec<Byte>& Operands);
    void ISUB(Vec<Byte>& Operands);
    void IMUL(Vec<Byte>& Operands);
    void IDIV(Vec<Byte>& Operands);
    void IPUSH(Vec<Byte>& Operands);
    void CPUSH(Vec<Byte>& Operands);
    void SPUSH(Vec<Byte>& Operands);
    void STOREG(Vec<Byte>& Operands);
    void STOREL(Vec<Byte>& Operands);
    void LOADG(Vec<Byte>& Operands);
    void LOADL(Vec<Byte>& Operands);
};
