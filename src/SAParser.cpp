#include "SAParser.h"
#include "Constants.h"

#include <sstream>
#include <stdexcept>
#include <iostream>
#include <algorithm>

SAParser::SAParser(const std::string& iPath)
{
    _file = std::ifstream(iPath);
}

std::vector<instruction_tuple_t> SAParser::parse()
{
    if (!_file.is_open()) {
        throw std::runtime_error("ERROR: Could not open .sa file, path does not exist!");
    }

    std::vector<instruction_tuple_t> aInstructionArray;
    int lineNb = 1;

    while (!_file.eof()) {
        std::string aLine;
        std::getline(_file, aLine);

        // Skip empty lines
        if (aLine.empty() || std::all_of(aLine.begin(), aLine.end(), isspace)){
            continue;
        }

        std::istringstream aLineStream(aLine);

        std::string aOffsetStr;
        std::string aInstruction;
        std::string aArgStr;

        std::getline(aLineStream, aOffsetStr, ' ');
        std::getline(aLineStream, aInstruction, ' ');
        std::getline(aLineStream, aArgStr, ' ');

        int32_t aOffset;
        int32_t aArg;
        StackAssemblyKeyword aInstructionKeyword;

        try {
            aOffset = std::stoi(aOffsetStr);

            if ( !(aArgStr.rfind("//", 0) == 0) && !aArgStr.empty()) {
                aArg =  std::stoi(aArgStr);
            }
        } catch (std::exception&) {
            _file.close();
            throw std::runtime_error("ERROR PARSING FILE (Line " + std::to_string(lineNb) + "): Instruction offset or argument is not an integer !");
        }

        try {
            aInstructionKeyword = kKeywordMap.at(aInstruction);
        } catch (std::exception&) {
            _file.close();
            throw std::runtime_error("ERROR PARSING FILE (Line " + std::to_string(lineNb) + "): Instruction " + aInstruction + " is not supported !");
        }

        aInstructionArray.push_back(std::make_tuple(aOffset, aInstructionKeyword, aArg));
        lineNb++;
    }

    return aInstructionArray;
}