#pragma once

#include <classes/instruction.hpp>
#include <types.hpp>

enum class ValueType {
    Int, Float, Bool
};

struct Value {
    ValueType Type;
    union {
        int i;
        float f;
        bool b;
    };

    Value(int Val) : Type(ValueType::Int), i(Val) {}
    Value(float Val) : Type(ValueType::Float), f(Val) {}
    Value(bool Val) : Type(ValueType::Bool), b(Val) {}

    Value() : Type(ValueType::Int), i(0) {}
};