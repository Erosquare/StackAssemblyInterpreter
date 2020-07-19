#ifndef __STACK_ASSEMBLY_ASSEMBLY_H__
#define __STACK_ASSEMBLY_ASSEMBLY_H__

#include <cstdint>
#include <stack>
#include <memory>

// The class representing the Assembly Machine
class StackAssemblyMachine {

friend class JumpIfZeroInstruction;

public:
    StackAssemblyMachine();
    virtual ~StackAssemblyMachine() {}

    int32_t popValue();
    void pushValue(int32_t iValue);

    size_t stackSize() const;

    void resetJumpOffset() { _jumpOffset = -1; }
    bool needsToJump() const { return (_jumpOffset >= 0); }
    int32_t getJumpOffset() const { return _jumpOffset; }

private:
    void setJumpToOffset(int32_t iOffset);

    std::stack<int32_t> _stack;
    int32_t _jumpOffset;
};

typedef std::shared_ptr<StackAssemblyMachine> StackAssemblyMachinePtr;

#endif