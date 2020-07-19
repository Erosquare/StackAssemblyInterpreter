#include "StackAssemblyProcessor.h"

StackAssemblyProcessor::StackAssemblyProcessor(const StackAssemblyMachinePtr& iMachinePtr): _machinePtr(iMachinePtr), _instructionsArray()
{
}

void StackAssemblyProcessor::executeAll()
{
    for (uint32_t currentOffset = 0; currentOffset < _instructionsArray.size(); currentOffset++) {

        // Perform the jump instruction if required
        if (_machinePtr->needsToJump()) {
            if (static_cast<uint32_t>(_machinePtr->getJumpOffset()) >= _instructionsArray.size()) {
                throw std::runtime_error("ERROR: Cannot jump, instruction offset #" + std::to_string(_machinePtr->getJumpOffset()) + "does not exist!");
            }
            currentOffset = _machinePtr->getJumpOffset();
            _machinePtr->resetJumpOffset();
        }

         if (_instructionsArray[currentOffset]->getIndex() != currentOffset) {
            throw std::runtime_error("ERROR: Current instruction offset (#" + std::to_string(_instructionsArray[currentOffset]->getIndex()) + ") is inconsistent. It should be #" + std::to_string(currentOffset));
        }

         _instructionsArray[currentOffset]->execute();
    }
}