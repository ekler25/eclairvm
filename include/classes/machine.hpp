#pragma once

#include <classes/frame.hpp>
#include <classes/value.hpp>
#include <classes/instruction.hpp>
#include <types.hpp>

struct Machine {
    Vec<Value> Variables;
    Vec<StackFrame> CallStack;
    Vec<Value> OperandStack;
    Vec<UPtr<String>> StringHeap;
    
    Vec<Instruction> Decode(Vec<Byte>& Bytecode);
    void Execute(Vec<Instruction> Inst);
};