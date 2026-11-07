#pragma once
#include "Token.hpp"
#include "Value.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace maz {

class MazException : public std::exception {
public:
    SourceLocation location;
    std::string message;
    std::string formatted;

    MazException(SourceLocation loc, std::string msg)
        : location(std::move(loc)), message(std::move(msg)) {
        std::ostringstream ss;
        ss << "[MAZ Error] ";
        if (!location.file.empty()) {
            ss << location.file << ":";
        }
        ss << location.line << ":" << location.column << ": " << message;
        formatted = ss.str();
    }

    const char* what() const noexcept override {
        return formatted.c_str();
    }
};

class ReturnException : public std::exception {
public:
    Token keyword;
    Value value;

    ReturnException(Token kw, Value val)
        : keyword(std::move(kw)), value(std::move(val)) {}
};

inline void reportDiagnostic(const std::string& source, const SourceLocation& loc, const std::string& msg) {
    std::cerr << "\n[MAZ Diagnostic] " 
              << (loc.file.empty() ? "<input>" : loc.file) 
              << ":" << loc.line << ":" << loc.column << "\n";
    std::cerr << "  Error: " << msg << "\n";

    // Extract line if source provided
    if (!source.empty() && loc.line > 0) {
        std::istringstream stream(source);
        std::string currentLine;
        size_t lineNum = 1;
        while (std::getline(stream, currentLine)) {
            if (lineNum == loc.line) {
                std::cerr << "    | " << currentLine << "\n";
                std::cerr << "    | ";
                for (size_t i = 1; i < loc.column && i <= currentLine.size(); ++i) {
                    std::cerr << " ";
                }
                std::cerr << "^\n";
                break;
            }
            lineNum++;
        }
    }
    std::cerr << std::endl;
}

} // namespace maz
