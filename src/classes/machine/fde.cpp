#include <iostream>
#include <classes/machine.hpp>
#include <types.hpp>

Vec<Instruction> Machine::Decode(Vec<Byte>& Bytecode) {
    Vec<Instruction> Instructions;

    int ByteIndex = 0;
    int BytecodeSize = Bytecode.size();

    while (ByteIndex < BytecodeSize) {
        OpCodes OpCode = (OpCodes)Bytecode[ByteIndex];

        auto OpInfoIt = OpCodeTable.find(OpCode);
        if (OpInfoIt == OpCodeTable.end())
            throw RuntimeError("[ \x1b[91mDecoding Error\x1b[0m ] invalid opcode at index " + std::to_string(ByteIndex));


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
    IP = 0;
    while (IP < Inst.size()) {
        auto& CurrentInstruction = Inst[IP];
        int RIP = IP;

        switch (CurrentInstruction.OpCode) {
            case OpCodes::JMP:   JMP(CurrentInstruction.Operands); break;
            case OpCodes::IPUSH: IPUSH(CurrentInstruction.Operands); break;
            case OpCodes::INVH:  INVH(CurrentInstruction.Operands); break;
            case OpCodes::CPUSH: CPUSH(CurrentInstruction.Operands); break;
            case OpCodes::CALL:  CALL(CurrentInstruction.Operands); break;
            case OpCodes::RET:   RET(CurrentInstruction.Operands); break;
            case OpCodes::IADD:  IADD(CurrentInstruction.Operands); break;
            case OpCodes::ISUB:  ISUB(CurrentInstruction.Operands); break;
            case OpCodes::IMUL:  IMUL(CurrentInstruction.Operands); break;
            case OpCodes::IDIV:  IDIV(CurrentInstruction.Operands); break;
            case OpCodes::SPUSH: SPUSH(CurrentInstruction.Operands); break;
            default: IP++; break;
        }

        if (IP == RIP) IP++;
    }
}
