#pragma once

#include <types.hpp>

enum class OpCodes {
    JMP, IPUSH, CALL, INVH,
    RET, EOP, IPOP, IADD, ISUB, IMUL, IDIV,
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