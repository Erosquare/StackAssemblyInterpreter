#include "InstructionFactory.h"
#include "StackAssemblyMachine.h"
#include "StackAssemblyProcessor.h"
#include "Constants.h"
#include "SAParser.h"

#include <iostream>
#include <vector>
#include <tuple>

/*  square.sa

    aProcessor.addInstruction(aFactory.buildInstruction(0, StackAssemblyKeyword::Read, std::nullopt));
    aProcessor.addInstruction(aFactory.buildInstruction(1, StackAssemblyKeyword::Dup, std::nullopt));
    aProcessor.addInstruction(aFactory.buildInstruction(2, StackAssemblyKeyword::Push, 0));
    aProcessor.addInstruction(aFactory.buildInstruction(3, StackAssemblyKeyword::LessThan, std::nullopt));
    aProcessor.addInstruction(aFactory.buildInstruction(4, StackAssemblyKeyword::Push, 8));
    aProcessor.addInstruction(aFactory.buildInstruction(5, StackAssemblyKeyword::JumpIfZero, std::nullopt));
    aProcessor.addInstruction(aFactory.buildInstruction(6, StackAssemblyKeyword::Pop, 1));
    aProcessor.addInstruction(aFactory.buildInstruction(7, StackAssemblyKeyword::Push, 0));
    aProcessor.addInstruction(aFactory.buildInstruction(8, StackAssemblyKeyword::Dup, std::nullopt));
    aProcessor.addInstruction(aFactory.buildInstruction(9, StackAssemblyKeyword::Mul, std::nullopt));
    aProcessor.addInstruction(aFactory.buildInstruction(10, StackAssemblyKeyword::Write, std::nullopt));
*/

/*
    factorial.sa

    aProcessor.addInstruction(aFactory.buildInstruction(0, StackAssemblyKeyword::Push, -1));
    aProcessor.addInstruction(aFactory.buildInstruction(1, StackAssemblyKeyword::Read, std::nullopt));
    aProcessor.addInstruction(aFactory.buildInstruction(2, StackAssemblyKeyword::Dup, std::nullopt));
    aProcessor.addInstruction(aFactory.buildInstruction(3, StackAssemblyKeyword::Push, 1));
    aProcessor.addInstruction(aFactory.buildInstruction(4, StackAssemblyKeyword::Rot, 2));
    aProcessor.addInstruction(aFactory.buildInstruction(5, StackAssemblyKeyword::Sub, std::nullopt));
    aProcessor.addInstruction(aFactory.buildInstruction(6, StackAssemblyKeyword::Dup, std::nullopt));
    aProcessor.addInstruction(aFactory.buildInstruction(7, StackAssemblyKeyword::Push, 1));
    aProcessor.addInstruction(aFactory.buildInstruction(8, StackAssemblyKeyword::LessThan, std::nullopt));
    aProcessor.addInstruction(aFactory.buildInstruction(9, StackAssemblyKeyword::Push, 2));
    aProcessor.addInstruction(aFactory.buildInstruction(10, StackAssemblyKeyword::JumpIfZero, std::nullopt));
    aProcessor.addInstruction(aFactory.buildInstruction(11, StackAssemblyKeyword::Mul, std::nullopt));
    aProcessor.addInstruction(aFactory.buildInstruction(12, StackAssemblyKeyword::Dup, std::nullopt));
    aProcessor.addInstruction(aFactory.buildInstruction(13, StackAssemblyKeyword::Push, 0));
    aProcessor.addInstruction(aFactory.buildInstruction(14, StackAssemblyKeyword::LessThan, std::nullopt));
    aProcessor.addInstruction(aFactory.buildInstruction(15, StackAssemblyKeyword::Push, 11));
    aProcessor.addInstruction(aFactory.buildInstruction(16, StackAssemblyKeyword::JumpIfZero, std::nullopt));
    aProcessor.addInstruction(aFactory.buildInstruction(17, StackAssemblyKeyword::Push, -1));
    aProcessor.addInstruction(aFactory.buildInstruction(18, StackAssemblyKeyword::Mul, std::nullopt));
    aProcessor.addInstruction(aFactory.buildInstruction(19, StackAssemblyKeyword::Dup, std::nullopt));
    aProcessor.addInstruction(aFactory.buildInstruction(20, StackAssemblyKeyword::Push, 0));
    aProcessor.addInstruction(aFactory.buildInstruction(21, StackAssemblyKeyword::LessThan, std::nullopt));
    aProcessor.addInstruction(aFactory.buildInstruction(22, StackAssemblyKeyword::Push, 25));
    aProcessor.addInstruction(aFactory.buildInstruction(23, StackAssemblyKeyword::JumpIfZero, std::nullopt));
    aProcessor.addInstruction(aFactory.buildInstruction(24, StackAssemblyKeyword::Push, 1));
    aProcessor.addInstruction(aFactory.buildInstruction(25, StackAssemblyKeyword::Write, std::nullopt));
*/

int main(int argc, char** argv) {   

    if (argc < 2) {
        std::cerr << "ERROR: No .sa file specified !" << std::endl;
        return -1;
    }

    StackAssemblyMachinePtr aMachinePtr(std::make_shared<StackAssemblyMachine>(StackAssemblyMachine())); // The concrete Assembly Machine
    InstructionFactory aFactory(aMachinePtr); // The Factory used to generate the Assembly Instructions to be executed
    StackAssemblyProcessor aProcessor(aMachinePtr); // The Processor that will execute all instructions in the program and handles code jumps

    SAParser aParser(argv[1]);

    try {
        std::vector<instruction_tuple_t> aInstructionArray = aParser.parse();

        for (const instruction_tuple_t& aTuple : aInstructionArray) {
            aProcessor.addInstruction(aFactory.buildInstruction(std::get<0>(aTuple), std::get<1>(aTuple), std::get<2>(aTuple)));
        }

        aProcessor.executeAll();
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
    
    return 0;
}