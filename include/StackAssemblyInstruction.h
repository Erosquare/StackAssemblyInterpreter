#ifndef __STACK_ASSEMBLY_INSTRUCTION_H__
#define __STACK_ASSEMBLY_INSTRUCTION_H__

#include <cstdint>
#include <string>
#include <istream>
#include <iostream>
#include <memory>
#include <functional>

#include "StackAssemblyMachine.h"

// Stack Assembly Instruction base class
class StackAssemblyInstruction {
public:
    StackAssemblyInstruction(uint32_t iCodeIndex, const std::string& iInstLabel, const StackAssemblyMachinePtr& iMachinePtr);
    virtual ~StackAssemblyInstruction() {}

    const std::string& getInstructionLabel() const { return _instLabel; }
    const uint32_t& getIndex() const { return _codeIndex; }

    virtual void execute() = 0; // Throws an exception if the instruction was wrongly executed

private:
    uint32_t _codeIndex; // Current instruction index in the program from 0 (first one) to N (last one)
    std::string _instLabel; // Instruction label name

protected:
    StackAssemblyMachinePtr _machinePtr; // Stack Assembly Machine processing the instructions
};

// Base class for instructions that takes one argument
class ParameterizedInstruction: public StackAssemblyInstruction {
public:
    ParameterizedInstruction(uint32_t iCodeIndex, const std::string& iInstLabel, const StackAssemblyMachinePtr& iMachinePtr, int32_t iArg)
                                                                        : StackAssemblyInstruction(iCodeIndex, iInstLabel, iMachinePtr), _arg(iArg) {}
    virtual ~ParameterizedInstruction() {}

    void execute() override {}; // Throws an exception if the instruction was wrongly executed

protected:
    int32_t _arg;
};

typedef std::shared_ptr<StackAssemblyInstruction> StackAssemblyInstructionPtr;

//////////////////// ASSEMBLY INSTRUCTIONS ////////////////////

/**
 * READ
 * 
 * Reads an integer on stdin and push the value on the stack, or
 * exit if input is invalid
 * 
 */
class ReadInstruction: public StackAssemblyInstruction {
public:
    ReadInstruction(uint32_t iCodeIndex, const StackAssemblyMachinePtr& iMachinePtr, std::istream& cin);
    virtual ~ReadInstruction() {}

    void execute() override; // Throws an exception if the instruction was wrongly executed

private:
    std::istream& _cin; // streams are not copyable since C++11 so we keep a reference on it
};


/**
 * WRITE
 * 
 * Pops the top value of the stack, and prints it on stdout
 * 
 */
class WriteInstruction: public StackAssemblyInstruction {
public:
    WriteInstruction(uint32_t iCodeIndex, const StackAssemblyMachinePtr& iMachinePtr, std::ostream& cout);
    virtual ~WriteInstruction() {}

    void execute() override; // Throws an exception if the instruction was wrongly executed

private:
    std::ostream& _cout; // streams are not copyable since C++11 so we keep a reference on it
};


/**
 * DUP
 * 
 * Duplicate the value on top of the stack
 * 
 */
class DupInstruction: public StackAssemblyInstruction {
public:
    DupInstruction(uint32_t iCodeIndex, const StackAssemblyMachinePtr& iMachinePtr);
    virtual ~DupInstruction() {}

    void execute() override; // Throws an exception if the instruction was wrongly executed
};


/**
 * ADD/SUB/MUL/DIV/MOD
 * 
 * Pops the two top values of the stack, applies the according math operator
 * between the top and second value then push the result on the top of the stack
 * 
 */
using operator_t = std::function<int32_t(int32_t,int32_t)>;
class OperationInstruction: public StackAssemblyInstruction {
public:
    OperationInstruction(uint32_t iCodeIndex, const std::string& iInstLabel, const StackAssemblyMachinePtr& iMachinePtr, operator_t iOperator);
    virtual ~OperationInstruction() {}

    void execute() override; // Throws an exception if the instruction was wrongly executed

private:
    int32_t compute(int32_t iFirstValue, int32_t iSecondValue);
    operator_t _operator;
};


/**
 * GT/LT/EQ
 * 
 * Pops the two top values from the stack, compare them for TOP >
 * SECOND (GT), TOP < SECOND (LT) or TOP == SECOND (EQ) and push the result as 0 or 1
 * 
 */
class ComparatorInstruction: public StackAssemblyInstruction {
public:
    ComparatorInstruction(uint32_t iCodeIndex, const std::string& iInstLabel, const StackAssemblyMachinePtr& iMachinePtr, operator_t iOperator);
    virtual ~ComparatorInstruction() {}

    void execute() override; // Throws an exception if the instruction was wrongly executed

private:
    bool compare(int32_t iFirstValue, int32_t iSecondValue);
    operator_t _operator;
};


/**
 * JMPZ
 * 
 * Pops the two top value of the stack. Jump to the <n>th
 * instruction, where <n> was the first value on the stack, if the
 * second value is null. Otherwise just drop these two values
 * 
 */
class JumpIfZeroInstruction: public StackAssemblyInstruction {
public:
    JumpIfZeroInstruction(uint32_t iCodeIndex, const StackAssemblyMachinePtr& iMachinePtr);
    virtual ~JumpIfZeroInstruction() {}

    void execute() override; // Throws an exception if the instruction was wrongly executed
};


/**
 * PUSH <n>
 * 
 * Push the integer value <n> on the stack
 * 
 */
class PushInstruction: public ParameterizedInstruction {
public:
    PushInstruction(uint32_t iCodeIndex, const StackAssemblyMachinePtr& iMachinePtr, int32_t iArg);
    virtual ~PushInstruction() {}

    void execute() override; // Throws an exception if the instruction was wrongly executed
};


/**
 * POP <n>
 * 
 * Push the integer value <n> on the stack
 * 
 */
class PopInstruction: public ParameterizedInstruction {
public:
    PopInstruction(uint32_t iCodeIndex, const StackAssemblyMachinePtr& iMachinePtr, int32_t iArg);
    virtual ~PopInstruction() {}

    void execute() override; // Throws an exception if the instruction was wrongly executed
};


/**
 * ROT <n>
 * 
 * Perform a circular rotation on the first n value of the stack
 * toward the top.
 * 
 * For instance the stack : BOTTOM [1,2,4,8] TOP becomes BOTTOM
 * [1, 8, 2, 4] TOP after ROT 3
 * 
 */
class RotationInstruction: public ParameterizedInstruction {
public:
    RotationInstruction(uint32_t iCodeIndex, const StackAssemblyMachinePtr& iMachinePtr, int32_t iArg);
    virtual ~RotationInstruction() {}

    void execute() override; // Throws an exception if the instruction was wrongly executed
};

#endif // __STACK_ASSEMBLY_INSTRUCTION_H__