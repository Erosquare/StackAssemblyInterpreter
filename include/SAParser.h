#ifndef __SAPARSER_H__
#define __SAPARSER_H__

#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <optional>

enum class StackAssemblyKeyword;
using instruction_tuple_t = std::tuple<uint32_t, StackAssemblyKeyword, std::optional<uint32_t>>;

class SAParser {
public:
    SAParser(const std::string& iFile);
    virtual ~SAParser() { _file.close(); }

    std::vector<instruction_tuple_t> parse();

private:
    std::ifstream _file;
};
#endif // __SAPARSER_H__