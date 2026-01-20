#pragma once

#include <classes/instruction.hpp>
#include <types.hpp>

enum class ValueType {
    Int, Float, Bool, Char
};

struct Value {
    ValueType Type;
    union {
        int i;
        float f;
        bool b;
        char c;
    };

    void InitInt(int Val) {
        Type = ValueType::Int;
        i = Val;
    }

    void InitFloat(float Val) {
        Type = ValueType::Float;
        f = Val;
    }

    void InitBool(bool Val) {
        Type = ValueType::Bool;
        b = Val;
    }

    void InitChar(char Val) {
        Type = ValueType::Char;
        c = Val;
    }
};
