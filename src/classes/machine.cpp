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
        if (OpInfoIt == OpCodeTable.end()) {
            throw std::runtime_error("[ \x1b[91mDecoding Error\x1b[0m ] invalid opcode at index " + std::to_string(ByteIndex));
        }

        int OperandSpec = OpInfoIt->second;
        Vec<Byte> Operands;

        if (OperandSpec == -1) {
            if (ByteIndex + 1 >= BytecodeSize) {
                throw std::runtime_error("[ \x1b[91mDecoding Error\x1b[0m ] missing operand length byte!");
            }

            Byte OperandLength = Bytecode[ByteIndex + 1];

            if (ByteIndex + 2 + OperandLength > BytecodeSize) {
                throw std::runtime_error("[ \x1b[91mDecoding Error\x1b[0m ] truncated variable length operands!");
            }

            Operands.insert(
                Operands.end(),
                Bytecode.begin() + (ByteIndex + 2),
                Bytecode.begin() + (ByteIndex + 2 + OperandLength)
            );

            ByteIndex += 2 + OperandLength;
        }

        else {
            int OperandCount = (int)OperandSpec;

            if (ByteIndex + 1 + OperandCount > BytecodeSize) {
                throw std::runtime_error("[ \x1b[91mDecoding Error\x1b[0m ] truncated fixed length operands!");
            }

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
    for (int i = 0; i < Inst.size(); i++) {
        std::cout << "[ \x1b[92mExecuting\x1b[0m ] Found instruction with ID \x1b[32m" << (int)Inst[i].OpCode << "\x1b[0m in address \x1b[92m" << i <<  "\x1b[0m\n";
    }
}