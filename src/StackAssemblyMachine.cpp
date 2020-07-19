#include "StackAssemblyMachine.h"

StackAssemblyMachine::StackAssemblyMachine(): _stack(), _jumpOffset(-1)
{
}

int32_t StackAssemblyMachine::popValue()
{
    int32_t aValue = _stack.top();
    _stack.pop();
    return aValue;
}

void StackAssemblyMachine::pushValue(int32_t iValue)
{
    _stack.push(iValue);
}

size_t StackAssemblyMachine::stackSize() const
{
    return _stack.size();
}

/**
 * jumpToOffset(int):
 * 
 * @int iOffset An index corresponding to the jump instruction
 * 
 * The Assembly Processor will try to jump to the specified
 * instruction offset.
 * 
 */
void StackAssemblyMachine::setJumpToOffset(int32_t iOffset)
{
    _jumpOffset = iOffset;
}
