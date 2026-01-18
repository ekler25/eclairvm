#pragma once

#include <classes/instruction.hpp>
#include <types.hpp>

struct StackFrame {
    int VarIndex;
    int VarReserve;
    int ReturnTo;
};