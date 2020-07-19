#ifndef __INSTRUCTION_FACTORY_H__
#define __INSTRUCTION_FACTORY_H__

#include "StackAssemblyInstruction.h"
#include "StackAssemblyMachine.h"
#include "Constants.h"

#include <optional>
#include <functional> 
#include <unordered_map>


class InstructionFactory {
public:
    InstructionFactory(const StackAssemblyMachinePtr& iMachinePtr);
    virtual ~InstructionFactory() {}

    StackAssemblyInstructionPtr buildInstruction(uint32_t iOffset, StackAssemblyKeyword iKeyword, std::optional<int32_t> iArg);

private:
    std::unordered_map<StackAssemblyKeyword, std::function<StackAssemblyInstructionPtr(uint32_t, std::optional<int32_t>)>> _factory;
};



#endif // __INSTRUCTION_FACTORY_H__