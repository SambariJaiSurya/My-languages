#include "lexer/Lexer.hpp"
#include "parser/Parser.hpp"
#include "runtime/Interpreter.hpp"
#include "common/Error.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace maz;

static const std::string MAZ_VERSION = "0.1.0-alpha";

void printHelp() {
    std::cout << "MAZ Programming Language CLI [v" << MAZ_VERSION << "]\n\n";
    std::cout << "Usage:\n";
    std::cout << "  maz run <file.maz>     Execute a MAZ source file\n";
    std::cout << "  maz repl               Start the interactive MAZ REPL\n";
    std::cout << "  maz --version, -v      Print the MAZ version\n";
    std::cout << "  maz --help, -h         Show this help message\n";
}

bool runSource(const std::string& source, const std::string& filename, Interpreter& interpreter) {
    try {
        Lexer lexer(source, filename);
        std::vector<Token> tokens = lexer.tokenize();

        Parser parser(tokens);
        std::shared_ptr<Program> program = parser.parse();

        interpreter.interpret(program);
        return true;
    } catch (const MazException& e) {
        reportDiagnostic(source, e.location, e.message);
        return false;
    } catch (const std::exception& e) {
        std::cerr << "[Fatal Error]: " << e.what() << std::endl;
        return false;
    }
}

int runFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "[Error]: Could not open file: " << path << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    Interpreter interpreter;
    bool success = runSource(source, path, interpreter);
    return success ? 0 : 1;
}

void runRepl() {
    std::cout << "========================================\n";
    std::cout << "  MAZ Interactive REPL [v" << MAZ_VERSION << "]\n";
    std::cout << "  Type 'exit' or press Ctrl+C to quit.\n";
    std::cout << "========================================\n\n";

    Interpreter interpreter;
    std::string line;

    while (true) {
        std::cout << "maz> ";
        if (!std::getline(std::cin, line)) {
            std::cout << "\nGoodbye!\n";
            break;
        }

        if (line == "exit" || line == "quit") {
            std::cout << "Goodbye!\n";
            break;
        }

        if (line.empty()) continue;

        runSource(line, "<repl>", interpreter);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        runRepl();
        return 0;
    }

    std::string arg1 = argv[1];

    if (arg1 == "--version" || arg1 == "-v") {
        std::cout << "MAZ version " << MAZ_VERSION << std::endl;
        return 0;
    }

    if (arg1 == "--help" || arg1 == "-h") {
        printHelp();
        return 0;
    }

    if (arg1 == "repl") {
        runRepl();
        return 0;
    }

    if (arg1 == "run") {
        if (argc < 3) {
            std::cerr << "[Error]: 'maz run' requires a file path.\n";
            std::cerr << "Usage: maz run <filename.maz>\n";
            return 1;
        }
        return runFile(argv[2]);
    }

    // Default fallback: if user just passed a filename ending in .maz
    if (arg1.size() > 4 && arg1.substr(arg1.size() - 4) == ".maz") {
        return runFile(arg1);
    }

    std::cerr << "[Error]: Unknown command or option '" << arg1 << "'.\n";
    printHelp();
    return 1;
}

