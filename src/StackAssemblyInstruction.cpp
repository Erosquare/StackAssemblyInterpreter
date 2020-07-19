#include "StackAssemblyInstruction.h"

#include <stdexcept>
#include <vector>
#include <limits>

StackAssemblyInstruction::StackAssemblyInstruction(uint32_t iCodeIndex, const std::string& iInstLabel, const StackAssemblyMachinePtr& iMachinePtr): _codeIndex(iCodeIndex), _instLabel(iInstLabel), _machinePtr(iMachinePtr)
{
}


/** READ Instruction **/
ReadInstruction::ReadInstruction(uint32_t iCodeIndex, const StackAssemblyMachinePtr& iMachinePtr, std::istream& cin): StackAssemblyInstruction(iCodeIndex, "READ", iMachinePtr), _cin(cin)
{
}

void ReadInstruction::execute()
{
    int32_t aValue;

    _cin >> aValue;

    if (!_cin) {
        throw std::runtime_error("ERROR (" + getInstructionLabel() + "#" + std::to_string(getIndex()) + "): entered value is not an integer!");
    }
    _machinePtr->pushValue(aValue);
}
/** END READ Instruction **/


/** WRITE Instruction **/
WriteInstruction::WriteInstruction(uint32_t iCodeIndex, const StackAssemblyMachinePtr& iMachinePtr, std::ostream& cout): StackAssemblyInstruction(iCodeIndex, "WRITE", iMachinePtr), _cout(cout)
{
}

void WriteInstruction::execute()
{
    if (_machinePtr->stackSize() < 1) {
        throw std::runtime_error("ERROR (" + getInstructionLabel() + "#" + std::to_string(getIndex()) + "): cannot display top value, stack is empty!");
    }

    int32_t aValue;

    aValue = _machinePtr->popValue();
    _cout << aValue << std::endl;
}
/** END WRITE Instruction **/


/** DUP Instruction **/
DupInstruction::DupInstruction(uint32_t iCodeIndex, const StackAssemblyMachinePtr& iMachinePtr): StackAssemblyInstruction(iCodeIndex, "DUP", iMachinePtr)
{
}

void DupInstruction::execute()
{
    if (_machinePtr->stackSize() < 1) {
        throw std::runtime_error("ERROR (" + getInstructionLabel() + "#" + std::to_string(getIndex()) + "): cannot duplicate top value, stack is empty!");
    }

    int32_t aValue;
    aValue = _machinePtr->popValue();

    _machinePtr->pushValue(aValue);
    _machinePtr->pushValue(aValue);
}
/** END DUP Instruction **/


/** ADD/SUB/MUL/DIV/MOD Instruction **/
OperationInstruction::OperationInstruction(uint32_t iCodeIndex, const std::string& iInstLabel, const StackAssemblyMachinePtr& iMachinePtr, operator_t iOperator): StackAssemblyInstruction(iCodeIndex, iInstLabel, iMachinePtr), _operator(iOperator)
{
}

void OperationInstruction::execute()
{
    if (_machinePtr->stackSize() < 2) {
        throw std::runtime_error("ERROR (" + getInstructionLabel() + "#" + std::to_string(getIndex()) + "): cannot process values, stack must have two values at least!");
    }

    int32_t aFirstValue = _machinePtr->popValue();
    int32_t aSecondValue = _machinePtr->popValue();

    _machinePtr->pushValue(compute(aFirstValue, aSecondValue));
}

int32_t OperationInstruction::compute(int32_t iFirstValue, int32_t iSecondValue)
{
    return _operator(iFirstValue, iSecondValue);
}
/** END ADD/SUB/MUL/DIV/MOD Instruction **/


/** GT/LT/EQ Instruction **/
ComparatorInstruction::ComparatorInstruction(uint32_t iCodeIndex, const std::string& iInstLabel, const StackAssemblyMachinePtr& iMachinePtr, operator_t iOperator): StackAssemblyInstruction(iCodeIndex, iInstLabel, iMachinePtr), _operator(iOperator)
{
}

void ComparatorInstruction::execute()
{
    if (_machinePtr->stackSize() < 2) {
        throw std::runtime_error("ERROR (" + getInstructionLabel() + "#" + std::to_string(getIndex()) + "): cannot compare values, stack must have two values at least!");
    }

    int32_t aFirstValue = _machinePtr->popValue();
    int32_t aSecondValue = _machinePtr->popValue();

    // Push 0 if the comparison is met (true), push 1 otherwise (false)
    if (compare(aFirstValue, aSecondValue)) {
        _machinePtr->pushValue(0);
    } else {
        _machinePtr->pushValue(1);
    }
}

bool ComparatorInstruction::compare(int32_t iFirstValue, int32_t iSecondValue)
{
    return _operator(iFirstValue, iSecondValue);
}
/** END GT/LT/EQ Instruction **/


/** JMPZ Instruction **/
JumpIfZeroInstruction::JumpIfZeroInstruction(uint32_t iCodeIndex, const StackAssemblyMachinePtr& iMachinePtr): StackAssemblyInstruction(iCodeIndex, "JMPZ", iMachinePtr)
{
}

void JumpIfZeroInstruction::execute()
{
    if (_machinePtr->stackSize() < 2) {
        throw std::runtime_error("ERROR (" + getInstructionLabel() + "#" + std::to_string(getIndex()) + "): cannot jump, stack must have two values at least!");
    }

    int32_t aCodeIndex = _machinePtr->popValue();
    int32_t aComparisionResult = _machinePtr->popValue();

    if (aComparisionResult == 0) {
        if (aCodeIndex < 0) {
            throw std::runtime_error("ERROR (" + getInstructionLabel() + "#" + std::to_string(getIndex()) + "): cannot jump, offset instruction cannot be negative!");
        }
        _machinePtr->setJumpToOffset(aCodeIndex);
    }
}
/** END JMPZ Instruction **/


/** PUSH Instruction **/
PushInstruction::PushInstruction(uint32_t iCodeIndex, const StackAssemblyMachinePtr& iMachinePtr, int32_t iArg): ParameterizedInstruction(iCodeIndex, "PUSH", iMachinePtr, iArg)
{
}

void PushInstruction::execute()
{
    _machinePtr->pushValue(_arg);
}
/** END PUSH Instruction **/


/** POP Instruction **/
PopInstruction::PopInstruction(uint32_t iCodeIndex, const StackAssemblyMachinePtr& iMachinePtr, int32_t iArg): ParameterizedInstruction(iCodeIndex, "POP", iMachinePtr, iArg)
{

}

void PopInstruction::execute()
{
    if (_arg < 0) {
        throw std::runtime_error("ERROR (" + getInstructionLabel() + "#" + std::to_string(getIndex()) + "): the argument cannot be negative!");
    }
    
    if (_machinePtr->stackSize() < static_cast<uint32_t>(_arg)) {
        throw std::runtime_error("ERROR (" + getInstructionLabel() + "#" + std::to_string(getIndex()) + "): cannot pop values, stack contains less than " + std::to_string(_arg) +   " values!");
    }

    for (size_t i = 0; i < static_cast<uint32_t>(_arg); i++) {
        _machinePtr->popValue();
    }
}
/** END POP Instruction **/


/** ROT Instruction **/
RotationInstruction::RotationInstruction(uint32_t iCodeIndex, const StackAssemblyMachinePtr& iMachinePtr, int32_t iArg): ParameterizedInstruction(iCodeIndex, "ROT", iMachinePtr, iArg)
{
}

void RotationInstruction::execute()
{
    if (_arg <= 0) {
        throw std::runtime_error("ERROR (" + getInstructionLabel() + "#" + std::to_string(getIndex()) + "): the argument cannot be null or negative!");
    }
    
    if (_machinePtr->stackSize() < static_cast<uint32_t>(_arg)) {
        throw std::runtime_error("ERROR (" + getInstructionLabel() + "#" + std::to_string(getIndex()) + "): cannot perform a circular rotation, stack contains less than " + std::to_string(_arg) +   " values!");
    }

    std::vector<int32_t> aValuesArray(_arg);
    int32_t aArraySize = _arg;

    for (size_t i = 0; i < static_cast<uint32_t>(_arg); i++) {
        aValuesArray[i] = _machinePtr->popValue();
    }

    _machinePtr->pushValue(aValuesArray[0]);

    for (int32_t i = aArraySize-1; i > 0; i--) {
        _machinePtr->pushValue(aValuesArray[i]);
    }
}
/** END ROT Instruction **/


