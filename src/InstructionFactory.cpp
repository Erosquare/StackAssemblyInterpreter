#include "InstructionFactory.h"

#include <iostream>
#include <memory>

InstructionFactory::InstructionFactory(const StackAssemblyMachinePtr& iMachinePtr)
{
    _factory = std::unordered_map<StackAssemblyKeyword, std::function<StackAssemblyInstructionPtr(uint32_t, std::optional<int32_t>)>>();

    // Lambda functions to generate the according operators
    auto mul = [] (auto aFirstValue, auto aSecondValue) { return aFirstValue * aSecondValue; };
    auto add = [] (auto aFirstValue, auto aSecondValue) { return aFirstValue + aSecondValue; };
    auto sub = [] (auto aFirstValue, auto aSecondValue) { return aFirstValue - aSecondValue; };
    auto div = [] (auto aFirstValue, auto aSecondValue) { return aFirstValue / aSecondValue; };
    auto mod = [] (auto aFirstValue, auto aSecondValue) { return aFirstValue % aSecondValue; };

    auto gt = [] (auto aFirstValue, auto aSecondValue) { return aFirstValue > aSecondValue; };
    auto lt = [] (auto aFirstValue, auto aSecondValue) { return aFirstValue < aSecondValue; };
    auto eq = [] (auto aFirstValue, auto aSecondValue) { return aFirstValue == aSecondValue; };


    _factory[StackAssemblyKeyword::Read] = [&iMachinePtr] (uint32_t iOffset, std::optional<int32_t> ){ return std::make_shared<ReadInstruction>(ReadInstruction(iOffset, iMachinePtr, std::cin)); };
    _factory[StackAssemblyKeyword::Write] = [&iMachinePtr] (uint32_t iOffset, std::optional<int32_t> ){ return std::make_shared<WriteInstruction>(WriteInstruction(iOffset, iMachinePtr, std::cout)); };
    _factory[StackAssemblyKeyword::Dup] = [&iMachinePtr] (uint32_t iOffset, std::optional<int32_t> ){ return std::make_shared<DupInstruction>(DupInstruction(iOffset, iMachinePtr)); };
    _factory[StackAssemblyKeyword::Mul] = [&iMachinePtr, &mul] (uint32_t iOffset, std::optional<int32_t> ){ return std::make_shared<OperationInstruction>(OperationInstruction(iOffset, "MUL", iMachinePtr, mul)); };
    _factory[StackAssemblyKeyword::Add] = [&iMachinePtr, &add] (uint32_t iOffset, std::optional<int32_t> ){ return std::make_shared<OperationInstruction>(OperationInstruction(iOffset, "ADD", iMachinePtr, add)); };
    _factory[StackAssemblyKeyword::Sub] = [&iMachinePtr, &sub] (uint32_t iOffset, std::optional<int32_t> ){ return std::make_shared<OperationInstruction>(OperationInstruction(iOffset, "SUB", iMachinePtr, sub)); };
    _factory[StackAssemblyKeyword::Div] = [&iMachinePtr, &div] (uint32_t iOffset, std::optional<int32_t> ){ return std::make_shared<OperationInstruction>(OperationInstruction(iOffset, "DIV", iMachinePtr, div)); };
    _factory[StackAssemblyKeyword::Mod] = [&iMachinePtr, &mod] (uint32_t iOffset, std::optional<int32_t> ){ return std::make_shared<OperationInstruction>(OperationInstruction(iOffset, "MOD", iMachinePtr, mod)); };
    _factory[StackAssemblyKeyword::GreaterThan] = [&iMachinePtr, &gt] (uint32_t iOffset, std::optional<int32_t> ){ return std::make_shared<ComparatorInstruction>(ComparatorInstruction(iOffset, "GT", iMachinePtr, gt)); };
    _factory[StackAssemblyKeyword::LessThan] = [&iMachinePtr, &lt] (uint32_t iOffset, std::optional<int32_t> ){ return std::make_shared<ComparatorInstruction>(ComparatorInstruction(iOffset, "LT", iMachinePtr, lt)); };
    _factory[StackAssemblyKeyword::Equal] = [&iMachinePtr, &eq] (uint32_t iOffset, std::optional<int32_t> ){ return std::make_shared<ComparatorInstruction>(ComparatorInstruction(iOffset, "EQ", iMachinePtr, eq)); };
    _factory[StackAssemblyKeyword::JumpIfZero] = [&iMachinePtr] (uint32_t iOffset, std::optional<int32_t> ){ return std::make_shared<JumpIfZeroInstruction>(JumpIfZeroInstruction(iOffset, iMachinePtr)); };
    _factory[StackAssemblyKeyword::Push] = [&iMachinePtr] (uint32_t iOffset, std::optional<int32_t> iArg){ return std::make_shared<PushInstruction>(PushInstruction(iOffset, iMachinePtr, iArg.value())); };
    _factory[StackAssemblyKeyword::Pop] = [&iMachinePtr] (uint32_t iOffset, std::optional<int32_t> iArg){ return std::make_shared<PopInstruction>(PopInstruction(iOffset, iMachinePtr, iArg.value())); };
    _factory[StackAssemblyKeyword::Rot] = [&iMachinePtr] (uint32_t iOffset, std::optional<int32_t> iArg){ return std::make_shared<RotationInstruction>(RotationInstruction(iOffset, iMachinePtr, iArg.value())); };
    _factory[StackAssemblyKeyword::Unknown] = [&iMachinePtr] (uint32_t, std::optional<int32_t>){ return nullptr; };
}

/**
 * buildInstruction(uint32_t, StackAssemblyKeyword, const std::vector<std::string>&):
 * 
 * @uint32_t iOffset An index corresponding to the instruction line number
 * @StackAssemblyKeyword iKeyword an enum corresponding to a Stack Assembly language keyword
 * @int32_t iArg Optional argument according to the instruction
 * 
 * @return StackAssemblyInstructionPtr A pointer to the Stack Assembly Instruction
 * 
 * Creates the assembly instruction to be executed by the processor.
 * 
 */
StackAssemblyInstructionPtr InstructionFactory::buildInstruction(uint32_t iOffset, StackAssemblyKeyword iKeyword, std::optional<int32_t> iArg)
{
    return _factory[iKeyword](iOffset, iArg);
}
