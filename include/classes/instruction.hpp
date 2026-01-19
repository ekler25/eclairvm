#pragma once

#include <types.hpp>

enum class OpCodes {
    JMP, IPUSH, CALL, INVH,
    RET, IPOP, IADD, ISUB, IMUL, IDIV,
    PUSHSTR
};

const Map<OpCodes, int> OpCodeTable = {
    {OpCodes::IPOP, 0},
    {OpCodes::IADD, 0},
    {OpCodes::ISUB, 0},
    {OpCodes::IMUL, 0},
    {OpCodes::IDIV, 0},
    {OpCodes::RET,  0},
    {OpCodes::EOP,  0},

    {OpCodes::JMP,  1},
    {OpCodes::IPUSH,1},
    {OpCodes::CALL, 1},
    {OpCodes::INVH, 1},

    {OpCodes::PUSHSTR, -1}
};

struct Instruction {
    OpCodes OpCode;
    Vec<Byte> Operands;

    Instruction(OpCodes OpCode, const Vec<Byte>& Operands = {})
        : OpCode(OpCode), Operands(Operands) {}
};

void JMP(int& Index, Vec<Byte>& Operands, const Vec<Instruction>& Inst);
void IPUSH(int& Index, Vec<Byte>& Operands, const Vec<Instruction>& Inst);
void CALL(int& Index, Vec<Byte>& Operands, const Vec<Instruction>& Inst);
void RET(int& Index, Vec<Byte>& Operands, const Vec<Instruction>& Inst);
void EOP(int& Index, Vec<Byte>& Operands, const Vec<Instruction>& Inst);
void IPOP(int& Index, Vec<Byte>& Operands, const Vec<Instruction>& Inst);
void IADD(int& Index, Vec<Byte>& Operands, const Vec<Instruction>& Inst);
void ISUB(int& Index, Vec<Byte>& Operands, const Vec<Instruction>& Inst);
void IMUL(int& Index, Vec<Byte>& Operands, const Vec<Instruction>& Inst);
void IDIV(int& Index, Vec<Byte>& Operands, const Vec<Instruction>& Inst);
