#pragma once

#include <classes/instruction.hpp>
#include <types.hpp>

enum class ValueType {
    Int, Float, Bool, Char, Str
};

struct Value {
    ValueType Type;
    int i;
    float f;
    bool b;
    char c;
    String s;

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

    void InitStr(String Val) {
        Type = ValueType::Str;
        s = Val;
    }
};
