#include <iostream>
#include <classes/machine.hpp>
#include <types.hpp>
#include <utils.hpp>

Vec<Instruction> Machine::Decode(Vec<Byte>& Bytecode) {
    Vec<Instruction> Instructions;
    
    int ByteIndex = 8;
    int BytecodeSize = Bytecode.size();

    if (BytecodeSize < 8)
        Err(Error::Header, "File does not contain EVM header");

    if (
        Bytecode[0] != 0x00 ||
        Bytecode[1] != 'E'  ||
        Bytecode[2] != 'V'  ||
        Bytecode[3] != 'M'
    ) Err(Error::Header, "EVM magic not found");

    if (EVMVersion != Bytecode[4]) 
        Err(Error::Header, "This program cannot be run by this version of EVM");

    this->Version = Bytecode[4];
    this->Flags = Bytecode[5];
    this->FunctionCount = ((Word)Bytecode[6] << 8) | Bytecode[7];

    GlobalFunctionTable.push_back(Function(
        0, 0, 0
    ));
    
    GlobalFunctionTable.resize(FunctionCount + 1);

    for (int f = 0; f < FunctionCount; f++) {
        Word ID = BytesToInt({ Bytecode[ByteIndex], Bytecode[ByteIndex + 1] });

        uint32 Addr = BytesToInt({
            Bytecode[ByteIndex + 2],
            Bytecode[ByteIndex + 3],
            Bytecode[ByteIndex + 4],
            Bytecode[ByteIndex + 5],
        });

        uint32 Locals = Bytecode[ByteIndex + 6];
        uint16 Args   = Bytecode[ByteIndex + 7];

        if (ID >= GlobalFunctionTable.size())
            Err(Error::Header, "Function identifier out of range");

        GlobalFunctionTable[ID] = Function(Addr, Locals, Args);

        ByteIndex += 8;
    }

    while (ByteIndex < BytecodeSize) {
        OpCodes OpCode = (OpCodes)Bytecode[ByteIndex];

        auto OpInfoIt = OpCodeTable.find(OpCode);
        if (OpInfoIt == OpCodeTable.end())
            Err(Error::Decoding, "Invalid opcode " + std::to_string(Bytecode[ByteIndex]) + " at index " + std::to_string(ByteIndex));
        
        int OperandSpec = OpInfoIt->second;
        Vec<Byte> Operands;

        if (OperandSpec == -1) {
            if (ByteIndex + 1 >= BytecodeSize)
                throw RuntimeError("[ \x1b[91mDecoding Error\x1b[0m ] missing operand length byte!\n");

            Byte OperandLength = Bytecode[ByteIndex + 1];

            if (ByteIndex + 2 + OperandLength > BytecodeSize)
                throw RuntimeError("[ \x1b[91mDecoding Error\x1b[0m ] truncated variable length operands!\n");

            Operands.insert(
                Operands.end(),
                Bytecode.begin() + (ByteIndex + 2),
                Bytecode.begin() + (ByteIndex + 2 + OperandLength)
            );

            ByteIndex += 2 + OperandLength;
        }

        else {
            int OperandCount = (int)OperandSpec;

            if (ByteIndex + 1 + OperandCount > BytecodeSize)
                throw RuntimeError("[ \x1b[91mDecoding Error\x1b[0m ] truncated fixed length operands!\n");

            if (OperandCount > 0) {
                Operands.insert(
                    Operands.end(),
                    Bytecode.begin() + (ByteIndex + 1),
                    Bytecode.begin() + (ByteIndex + 1 + OperandCount)
                );
            }

            ByteIndex += 1 + OperandCount;
        }

        Instructions.emplace_back(OpCode, Operands);
    }

    return Instructions;
}

void Machine::Execute(Vec<Instruction> Inst) {
    Vec<Byte> EntryPointAddr = { 0x00 };
    CALL(EntryPointAddr);

    IP = 0;
    while (IP < Inst.size()) {
        auto& CurrentInstruction = Inst[IP];
        int RIP = IP;

        switch (CurrentInstruction.OpCode) {
            case OpCodes::JMP:     JMP(CurrentInstruction.Operands); break;
            case OpCodes::IPUSH:   IPUSH(CurrentInstruction.Operands); break;
            case OpCodes::INVH:    INVH(CurrentInstruction.Operands); break;
            case OpCodes::CPUSH:   CPUSH(CurrentInstruction.Operands); break;
            case OpCodes::CALL:    CALL(CurrentInstruction.Operands); break;
            case OpCodes::RET:     RET(CurrentInstruction.Operands); break;
            case OpCodes::IADD:    IADD(CurrentInstruction.Operands); break;
            case OpCodes::ISUB:    ISUB(CurrentInstruction.Operands); break;
            case OpCodes::IMUL:    IMUL(CurrentInstruction.Operands); break;
            case OpCodes::IDIV:    IDIV(CurrentInstruction.Operands); break;
            case OpCodes::SPUSH:   SPUSH(CurrentInstruction.Operands); break;
            case OpCodes::STOREG:  STOREG(CurrentInstruction.Operands); break;
            case OpCodes::LOADG:   LOADG(CurrentInstruction.Operands); break;
            case OpCodes::STOREL:  STOREL(CurrentInstruction.Operands); break;
            case OpCodes::LOADL:   LOADL(CurrentInstruction.Operands); break;
            default: IP++; break;
        }

        if (IP == RIP) IP++;
    }
}
