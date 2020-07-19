#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <unordered_map>

enum class StackAssemblyKeyword
{
    Unknown,
    Read,
    Write,
    Dup,
    Mul,
    Add,
    Sub,
    Div,
    Mod,
    GreaterThan,
    LessThan,
    Equal,
    JumpIfZero,
    Push,
    Pop,
    Rot,
    MaxNb
};

static std::unordered_map<std::string, StackAssemblyKeyword> kKeywordMap = {
    {"READ", StackAssemblyKeyword::Read},
    {"WRITE", StackAssemblyKeyword::Write},
    {"DUP", StackAssemblyKeyword::Dup},
    {"MUL", StackAssemblyKeyword::Mul},
    {"ADD", StackAssemblyKeyword::Add},
    {"SUB", StackAssemblyKeyword::Sub},
    {"DIV", StackAssemblyKeyword::Div},
    {"MOD", StackAssemblyKeyword::Mod},
    {"GT", StackAssemblyKeyword::GreaterThan},
    {"LT", StackAssemblyKeyword::LessThan},
    {"EQ", StackAssemblyKeyword::Equal},
    {"JUMPZ", StackAssemblyKeyword::JumpIfZero},
    {"PUSH", StackAssemblyKeyword::Push},
    {"POP", StackAssemblyKeyword::Pop},
    {"ROT", StackAssemblyKeyword::Rot}
};

#endif // __CONSTANTS_H__