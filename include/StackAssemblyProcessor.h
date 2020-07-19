#ifndef __STACK_ASSEMBLY_PROCESSOR_H__
#define __STACK_ASSEMBLY_PROCESSOR_H__

#include <vector>

#include "StackAssemblyInstruction.h"
#include "StackAssemblyMachine.h"


// The class the will execute all the instructions in the
// program and will update the Assembly Machine state
class StackAssemblyProcessor {
public:
    StackAssemblyProcessor(const StackAssemblyMachinePtr& iMachinePtr);
    virtual ~StackAssemblyProcessor() {}

    void addInstruction(const StackAssemblyInstructionPtr& iInstructionPtr) { _instructionsArray.push_back(iInstructionPtr); }
    void executeAll();

private:
    StackAssemblyMachinePtr _machinePtr;
    std::vector<StackAssemblyInstructionPtr> _instructionsArray;
};

#endif // __STACK_ASSEMBLY_PROCESSOR_H__