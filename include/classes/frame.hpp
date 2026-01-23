#pragma once

#include <classes/instruction.hpp>
#include <classes/value.hpp>
#include <types.hpp>

struct Function {
    uint32 Address;
    uint32 Locals;
    uint16 Args;

    Function() = default;
    Function(uint32 Ad, uint32 Lo, uint16 Ar) : Address(Ad), Locals(Lo), Args(Ar) {}
};

struct CallStackFrame {
    uint32 ReturnAddress;
    uint32 VarPtr;
    uint32 VarSlots;

    CallStackFrame(uint32 Ra, uint32 Vp, uint32 Vs) : ReturnAddress(Ra), VarPtr(Vp), VarSlots(Vs) {}
};
