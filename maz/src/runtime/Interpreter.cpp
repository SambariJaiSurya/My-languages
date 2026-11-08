#include "Interpreter.hpp"
#include "../common/Error.hpp"
#include <iostream>
#include <chrono>
#include <string>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <numeric>
#include <numbers>
#include <limits>

namespace maz {

Interpreter::Interpreter() {
    globals = std::make_shared<Environment>();
    currentEnv = globals;
    registerBuiltins();
}

static std::string trimString(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

void Interpreter::registerBuiltins() {
    // Rule 5: display() standard output function
    NativeFn displayFn = [](const std::vector<Value>& args) -> Value {
        for (size_t i = 0; i < args.size(); ++i) {
            std::cout << args[i].toString();
            if (i + 1 < args.size()) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
        return Value::makeNull();
    };
    globals->define("display", Value(displayFn), true, false);

    // Built-in clock for timing/benchmarks
    NativeFn clockFn = [](const std::vector<Value>&) -> Value {
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        return Value(static_cast<double>(duration.count()) / 1000.0);
    };
    globals->define("clock", Value(clockFn), true, false);

    // Rule 73: MAZ Input System (lowercase primary, camelCase alias)
    // 1. input(prompt?) — Universal input
    NativeFn inputFn = [](const std::vector<Value>& args) -> Value {
        if (!args.empty()) {
            std::cout << args[0].toString() << std::flush;
        }
        std::string line;
        if (!std::getline(std::cin, line)) {
            line = "";
        }
        return Value(line);
    };
    globals->define("input", Value(inputFn), true, false);

    // 2. inputint(prompt?) — Integer input (with inputInt alias)
    NativeFn inputIntFn = [](const std::vector<Value>& args) -> Value {
        if (!args.empty()) {
            std::cout << args[0].toString() << std::flush;
        }
        std::string raw;
        if (!std::getline(std::cin, raw)) {
            throw MazException(SourceLocation{}, "inputint(): unexpected end of input");
        }
        std::string trimmed = trimString(raw);
        if (trimmed.empty()) {
            throw MazException(SourceLocation{}, "inputint(): expected an integer, but received empty input");
        }
        try {
            size_t idx = 0;
            int64_t val = std::stoll(trimmed, &idx);
            if (idx != trimmed.size()) {
                throw MazException(SourceLocation{}, "inputint(): invalid integer format '" + trimmed + "'");
            }
            return Value(val);
        } catch (const MazException&) {
            throw;
        } catch (...) {
            throw MazException(SourceLocation{}, "inputint(): invalid integer format '" + trimmed + "'");
        }
    };
    globals->define("inputint", Value(inputIntFn), true, false);
    globals->define("inputInt", Value(inputIntFn), true, false);

    // 3. inputfloat(prompt?) — Floating-point input (with inputFloat alias)
    NativeFn inputFloatFn = [](const std::vector<Value>& args) -> Value {
        if (!args.empty()) {
            std::cout << args[0].toString() << std::flush;
        }
        std::string raw;
        if (!std::getline(std::cin, raw)) {
            throw MazException(SourceLocation{}, "inputfloat(): unexpected end of input");
        }
        std::string trimmed = trimString(raw);
        if (trimmed.empty()) {
            throw MazException(SourceLocation{}, "inputfloat(): expected a float, but received empty input");
        }
        try {
            size_t idx = 0;
            double val = std::stod(trimmed, &idx);
            if (idx != trimmed.size()) {
                throw MazException(SourceLocation{}, "inputfloat(): invalid floating-point format '" + trimmed + "'");
            }
            return Value(val);
        } catch (const MazException&) {
            throw;
        } catch (...) {
            throw MazException(SourceLocation{}, "inputfloat(): invalid floating-point format '" + trimmed + "'");
        }
    };
    globals->define("inputfloat", Value(inputFloatFn), true, false);
    globals->define("inputFloat", Value(inputFloatFn), true, false);

    // 4. inputbool(prompt?) — Boolean input (with inputBool alias)
    NativeFn inputBoolFn = [](const std::vector<Value>& args) -> Value {
        if (!args.empty()) {
            std::cout << args[0].toString() << std::flush;
        }
        std::string raw;
        if (!std::getline(std::cin, raw)) {
            throw MazException(SourceLocation{}, "inputbool(): unexpected end of input");
        }
        std::string trimmed = trimString(raw);
        std::string lower = trimmed;
        std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) { return std::tolower(c); });

        if (lower == "true") {
            return Value::makeBool(true);
        } else if (lower == "false") {
            return Value::makeBool(false);
        } else {
            throw MazException(SourceLocation{}, "inputbool(): invalid Boolean '" + trimmed + "' (expected 'true' or 'false')");
        }
    };
    globals->define("inputbool", Value(inputBoolFn), true, false);
    globals->define("inputBool", Value(inputBoolFn), true, false);

    // 5. inputstring(prompt?) — String input (with inputString alias)
    NativeFn inputStringFn = [](const std::vector<Value>& args) -> Value {
        if (!args.empty()) {
            std::cout << args[0].toString() << std::flush;
        }
        std::string line;
        if (!std::getline(std::cin, line)) {
            line = "";
        }
        return Value(line);
    };
    globals->define("inputstring", Value(inputStringFn), true, false);
    globals->define("inputString", Value(inputStringFn), true, false);

    // ==========================================
    // Phase 1 & 2 Math Standard Library
    // ==========================================

    // Constants
    globals->define("PI", Value(3.14159265358979323846), true, false);
    globals->define("TAU", Value(6.28318530717958647692), true, false);
    globals->define("E", Value(2.71828182845904523536), true, false);
    globals->define("SQRT2", Value(1.41421356237309504880), true, false);
    globals->define("SQRT3", Value(1.73205080756887729352), true, false);
    globals->define("LN2", Value(0.69314718055994530941), true, false);
    globals->define("LN10", Value(2.30258509299404568401), true, false);
    globals->define("INF", Value(std::numeric_limits<double>::infinity()), true, false);
    globals->define("NAN_VAL", Value(std::numeric_limits<double>::quiet_NaN()), true, false);

    // Basic Math
    globals->define("abs", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value(0LL);
        if (args[0].isInt()) return Value(std::abs(args[0].asInt()));
        return Value(std::abs(args[0].asFloat()));
    }), true, false);

    globals->define("min", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.size() < 2) return args.empty() ? Value(0LL) : args[0];
        if (args[0].isInt() && args[1].isInt()) return Value(std::min(args[0].asInt(), args[1].asInt()));
        return Value(std::min(args[0].asFloat(), args[1].asFloat()));
    }), true, false);

    globals->define("max", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.size() < 2) return args.empty() ? Value(0LL) : args[0];
        if (args[0].isInt() && args[1].isInt()) return Value(std::max(args[0].asInt(), args[1].asInt()));
        return Value(std::max(args[0].asFloat(), args[1].asFloat()));
    }), true, false);

    globals->define("pow", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.size() < 2) return Value(0.0);
        return Value(std::pow(args[0].asFloat(), args[1].asFloat()));
    }), true, false);

    globals->define("sqrt", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value(0.0);
        double val = args[0].asFloat();
        if (val < 0) throw MazException(SourceLocation{}, "Domain error: sqrt() of negative number");
        return Value(std::sqrt(val));
    }), true, false);

    globals->define("cbrt", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value(0.0);
        return Value(std::cbrt(args[0].asFloat()));
    }), true, false);

    globals->define("hypot", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.size() < 2) return Value(0.0);
        return Value(std::hypot(args[0].asFloat(), args[1].asFloat()));
    }), true, false);

    globals->define("sign", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value(0LL);
        double val = args[0].asFloat();
        if (val > 0) return Value(1LL);
        if (val < 0) return Value(-1LL);
        return Value(0LL);
    }), true, false);

    globals->define("square", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value(0LL);
        if (args[0].isInt()) return Value(args[0].asInt() * args[0].asInt());
        return Value(args[0].asFloat() * args[0].asFloat());
    }), true, false);

    globals->define("clamp", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.size() < 3) return Value(0.0);
        double val = args[0].asFloat(), mn = args[1].asFloat(), mx = args[2].asFloat();
        return Value(std::clamp(val, mn, mx));
    }), true, false);

    // Rounding & Number Conversion
    globals->define("round", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value(0LL);
        return Value(static_cast<int64_t>(std::round(args[0].asFloat())));
    }), true, false);

    globals->define("floor", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value(0LL);
        return Value(static_cast<int64_t>(std::floor(args[0].asFloat())));
    }), true, false);

    globals->define("ceil", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value(0LL);
        return Value(static_cast<int64_t>(std::ceil(args[0].asFloat())));
    }), true, false);

    globals->define("trunc", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value(0LL);
        return Value(static_cast<int64_t>(std::trunc(args[0].asFloat())));
    }), true, false);

    globals->define("round_to", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.size() < 2) return args.empty() ? Value(0.0) : args[0];
        double val = args[0].asFloat();
        int64_t n = args[1].asInt();
        double factor = std::pow(10.0, n);
        return Value(std::round(val * factor) / factor);
    }), true, false);

    globals->define("is_integer", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value::makeBool(false);
        if (args[0].isInt()) return Value::makeBool(true);
        double val = args[0].asFloat();
        return Value::makeBool(std::floor(val) == val);
    }), true, false);

    // Trigonometry
    globals->define("sin", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value(0.0);
        return Value(std::sin(args[0].asFloat()));
    }), true, false);

    globals->define("cos", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value(0.0);
        return Value(std::cos(args[0].asFloat()));
    }), true, false);

    globals->define("tan", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value(0.0);
        return Value(std::tan(args[0].asFloat()));
    }), true, false);

    globals->define("asin", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value(0.0);
        return Value(std::asin(args[0].asFloat()));
    }), true, false);

    globals->define("acos", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value(0.0);
        return Value(std::acos(args[0].asFloat()));
    }), true, false);

    globals->define("atan", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value(0.0);
        return Value(std::atan(args[0].asFloat()));
    }), true, false);

    globals->define("atan2", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.size() < 2) return Value(0.0);
        return Value(std::atan2(args[0].asFloat(), args[1].asFloat()));
    }), true, false);

    globals->define("radians", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value(0.0);
        return Value(args[0].asFloat() * (3.14159265358979323846 / 180.0));
    }), true, false);

    globals->define("degrees", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value(0.0);
        return Value(args[0].asFloat() * (180.0 / 3.14159265358979323846));
    }), true, false);

    // Logarithms & Exponentials
    globals->define("exp", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value(1.0);
        return Value(std::exp(args[0].asFloat()));
    }), true, false);

    globals->define("log", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value(0.0);
        double val = args[0].asFloat();
        if (val <= 0) throw MazException(SourceLocation{}, "Domain error: log() of non-positive number");
        return Value(std::log(val));
    }), true, false);

    globals->define("log10", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value(0.0);
        double val = args[0].asFloat();
        if (val <= 0) throw MazException(SourceLocation{}, "Domain error: log10() of non-positive number");
        return Value(std::log10(val));
    }), true, false);

    globals->define("log2", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value(0.0);
        double val = args[0].asFloat();
        if (val <= 0) throw MazException(SourceLocation{}, "Domain error: log2() of non-positive number");
        return Value(std::log2(val));
    }), true, false);

    // Number Theory (Competitive Programming)
    globals->define("gcd", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.size() < 2) return args.empty() ? Value(0LL) : args[0];
        return Value(std::gcd(args[0].asInt(), args[1].asInt()));
    }), true, false);

    globals->define("lcm", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.size() < 2) return args.empty() ? Value(0LL) : args[0];
        return Value(std::lcm(args[0].asInt(), args[1].asInt()));
    }), true, false);

    globals->define("factorial", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value(1LL);
        int64_t n = args[0].asInt();
        if (n < 0) throw MazException(SourceLocation{}, "Domain error: factorial() of negative number");
        int64_t res = 1;
        for (int64_t i = 2; i <= n; ++i) res *= i;
        return Value(res);
    }), true, false);

    globals->define("is_prime", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value::makeBool(false);
        int64_t n = args[0].asInt();
        if (n <= 1) return Value::makeBool(false);
        if (n <= 3) return Value::makeBool(true);
        if (n % 2 == 0 || n % 3 == 0) return Value::makeBool(false);
        for (int64_t i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return Value::makeBool(false);
        }
        return Value::makeBool(true);
    }), true, false);

    globals->define("is_even", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value::makeBool(false);
        return Value::makeBool(args[0].asInt() % 2 == 0);
    }), true, false);

    globals->define("is_odd", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value::makeBool(false);
        return Value::makeBool(args[0].asInt() % 2 != 0);
    }), true, false);

    globals->define("is_power_of_two", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value::makeBool(false);
        int64_t n = args[0].asInt();
        return Value::makeBool(n > 0 && (n & (n - 1)) == 0);
    }), true, false);

    globals->define("mod_pow", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.size() < 3) return Value(0LL);
        int64_t base = args[0].asInt(), exp = args[1].asInt(), mod = args[2].asInt();
        if (mod <= 0) throw MazException(SourceLocation{}, "mod_pow(): modulus must be positive");
        int64_t res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % mod;
            base = (base * base) % mod;
            exp /= 2;
        }
        return Value(res);
    }), true, false);

    globals->define("fibonacci", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value(0LL);
        int64_t n = args[0].asInt();
        if (n <= 0) return Value(0LL);
        if (n == 1) return Value(1LL);
        int64_t a = 0, b = 1;
        for (int64_t i = 2; i <= n; ++i) {
            int64_t c = a + b;
            a = b;
            b = c;
        }
        return Value(b);
    }), true, false);

    globals->define("nCr", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.size() < 2) return Value(0LL);
        int64_t n = args[0].asInt(), r = args[1].asInt();
        if (r < 0 || r > n) return Value(0LL);
        if (r == 0 || r == n) return Value(1LL);
        if (r > n / 2) r = n - r;
        int64_t res = 1;
        for (int64_t i = 1; i <= r; ++i) {
            res = res * (n - i + 1) / i;
        }
        return Value(res);
    }), true, false);

    globals->define("nPr", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.size() < 2) return Value(0LL);
        int64_t n = args[0].asInt(), r = args[1].asInt();
        if (r < 0 || r > n) return Value(0LL);
        int64_t res = 1;
        for (int64_t i = 0; i < r; ++i) {
            res *= (n - i);
        }
        return Value(res);
    }), true, false);

    // Bitwise Math
    globals->define("popcount", Value::makeNative([](const std::vector<Value>& args) -> Value {
        if (args.empty()) return Value(0LL);
        return Value(static_cast<int64_t>(std::popcount(static_cast<uint64_t>(args[0].asInt()))));
    }), true, false);
}

void Interpreter::interpret(const std::shared_ptr<Program>& program) {
    if (program) {
        program->accept(*this);
    }
}

Value Interpreter::evaluate(Expr& expr) {
    expr.accept(*this);
    return lastEvaluatedValue;
}

void Interpreter::execute(Stmt& stmt) {
    stmt.accept(*this);
}

void Interpreter::executeBlock(const std::vector<StmtPtr>& statements, std::shared_ptr<Environment> env) {
    std::shared_ptr<Environment> previous = currentEnv;
    try {
        currentEnv = env;
        for (const auto& stmt : statements) {
            if (stmt) execute(*stmt);
        }
    } catch (...) {
        currentEnv = previous;
        throw;
    }
    currentEnv = previous;
}

// Statements
void Interpreter::visitProgram(Program& program) {
    for (const auto& stmt : program.statements) {
        if (stmt) execute(*stmt);
    }
}

void Interpreter::visitExpressionStmt(ExpressionStmt& stmt) {
    if (stmt.expression) {
        evaluate(*stmt.expression);
    }
}

void Interpreter::visitVarDeclStmt(VarDeclStmt& stmt) {
    if (currentEnv->existsCurrentScope(stmt.name.lexeme) && !stmt.isNew) {
        throw MazException(stmt.name.location, "Error: Variable '" + stmt.name.lexeme + "' is already declared in this scope.");
    }

    Value value = Value::makeNull();
    bool isInit = false;
    if (stmt.initializer) {
        value = evaluate(*stmt.initializer);
        isInit = true;

        if (stmt.explicitType != ValueType::Null && stmt.explicitType != value.type) {
            if (stmt.explicitType == ValueType::Float && value.isInt()) {
                value = Value(static_cast<double>(value.asInt()));
            } else {
                std::string expectedName = "variable";
                if (stmt.explicitType == ValueType::Int) expectedName = "an integer";
                else if (stmt.explicitType == ValueType::Float) expectedName = "a float";
                else if (stmt.explicitType == ValueType::String) expectedName = "a string";
                else if (stmt.explicitType == ValueType::Bool) expectedName = "a boolean";

                throw MazException(stmt.name.location,
                    "Type Error: Cannot assign " + value.typeName() + " to " + expectedName + " variable '" + stmt.name.lexeme + "'.");
            }
        }
    } else {
        if (stmt.isConst) {
            throw MazException(stmt.name.location, "Error: Constant '" + stmt.name.lexeme + "' must be initialized upon declaration.");
        }
    }

    currentEnv->define(stmt.name.lexeme, value, stmt.isConst, stmt.isDyn, isInit, stmt.explicitType);
}

void Interpreter::visitMultiVarDeclStmt(MultiVarDeclStmt& stmt) {
    for (const auto& decl : stmt.declarations) {
        if (decl) visitVarDeclStmt(*decl);
    }
}

void Interpreter::visitGlobalStmt(GlobalStmt& stmt) {
    currentEnv->markGlobal(stmt.name.lexeme);
}

void Interpreter::visitBlockStmt(BlockStmt& stmt) {
    executeBlock(stmt.statements, std::make_shared<Environment>(currentEnv));
}

void Interpreter::visitIfStmt(IfStmt& stmt) {
    Value cond = evaluate(*stmt.condition);
    if (cond.isTruthy()) {
        execute(*stmt.thenBranch);
    } else if (stmt.elseBranch) {
        execute(*stmt.elseBranch);
    }
}

void Interpreter::visitWhileStmt(WhileStmt& stmt) {
    while (evaluate(*stmt.condition).isTruthy()) {
        execute(*stmt.body);
    }
}

// Rule 7: Three-part loop with commas and 'new' scoping
void Interpreter::visitForStmt(ForStmt& stmt) {
    std::shared_ptr<Environment> loopEnv = currentEnv;

    if (stmt.hasNew) {
        // 'new' creates a loop-local scope that shadows outer variables
        loopEnv = std::make_shared<Environment>(currentEnv);
    }

    std::shared_ptr<Environment> previous = currentEnv;
    currentEnv = loopEnv;

    try {
        if (stmt.initializer) {
            execute(*stmt.initializer);
        }

        while (true) {
            if (stmt.condition) {
                Value cond = evaluate(*stmt.condition);
                if (!cond.isTruthy()) break;
            }

            if (stmt.body) {
                execute(*stmt.body);
            }

            if (stmt.update) {
                evaluate(*stmt.update);
            }
        }
    } catch (...) {
        currentEnv = previous;
        throw;
    }

    currentEnv = previous;
}

void Interpreter::visitFunctionStmt(FunctionStmt& stmt) {
    auto fn = std::make_shared<MazFunction>();
    fn->name = stmt.name.lexeme;

    for (const auto& [paramToken, defaultExpr] : stmt.parameters) {
        fn->params.emplace_back(paramToken.lexeme, defaultExpr);
    }
    fn->body = stmt.body;
    fn->closure = currentEnv;

    currentEnv->define(stmt.name.lexeme, Value(fn), false, false);
}

void Interpreter::visitReturnStmt(ReturnStmt& stmt) {
    Value value = Value::makeNull();
    if (stmt.value) {
        value = evaluate(*stmt.value);
    }
    throw ReturnException(stmt.keyword, value);
}

// Expressions
void Interpreter::visitLiteralExpr(LiteralExpr& expr) {
    lastEvaluatedValue = expr.value;
}

void Interpreter::visitVariableExpr(VariableExpr& expr) {
    lastEvaluatedValue = currentEnv->get(expr.name);
}

void Interpreter::visitAssignExpr(AssignExpr& expr) {
    Value val = evaluate(*expr.value);
    currentEnv->assign(expr.name, val, expr.isForce);
    lastEvaluatedValue = val;
}

void Interpreter::visitUpdateExpr(UpdateExpr& expr) {
    Value currentVal = currentEnv->get(expr.name);
    Value newVal;

    if (currentVal.isInt()) {
        int64_t v = currentVal.asInt();
        if (expr.op.type == TokenType::TOKEN_PLUS_PLUS) {
            newVal = Value(v + 1);
        } else {
            newVal = Value(v - 1);
        }
    } else if (currentVal.isFloat()) {
        double v = currentVal.asFloat();
        if (expr.op.type == TokenType::TOKEN_PLUS_PLUS) {
            newVal = Value(v + 1.0);
        } else {
            newVal = Value(v - 1.0);
        }
    } else {
        throw MazException(expr.op.location, "Operand of increment/decrement must be a number.");
    }

    currentEnv->assign(expr.name, newVal, false);
    lastEvaluatedValue = expr.isPrefix ? newVal : currentVal;
}

void Interpreter::visitBinaryExpr(BinaryExpr& expr) {
    // Short-circuiting for logical operators
    if (expr.op.type == TokenType::TOKEN_OR_OR) {
        Value left = evaluate(*expr.left);
        if (left.isTruthy()) {
            lastEvaluatedValue = left;
            return;
        }
        lastEvaluatedValue = evaluate(*expr.right);
        return;
    }
    if (expr.op.type == TokenType::TOKEN_AND_AND) {
        Value left = evaluate(*expr.left);
        if (!left.isTruthy()) {
            lastEvaluatedValue = left;
            return;
        }
        lastEvaluatedValue = evaluate(*expr.right);
        return;
    }

    Value left = evaluate(*expr.left);
    Value right = evaluate(*expr.right);

    switch (expr.op.type) {
        case TokenType::TOKEN_PLUS: {
            // String concatenation takes precedence if either operand is string
            if (left.isString() || right.isString()) {
                lastEvaluatedValue = Value(left.toString() + right.toString());
                return;
            }
            if (left.isInt() && right.isInt()) {
                lastEvaluatedValue = Value(left.asInt() + right.asInt());
                return;
            }
            if (left.isNumber() && right.isNumber()) {
                lastEvaluatedValue = Value(left.asFloat() + right.asFloat());
                return;
            }
            throw MazException(expr.op.location, "Operands of '+' must be numbers or strings.");
        }
        case TokenType::TOKEN_MINUS: {
            if (left.isInt() && right.isInt()) {
                lastEvaluatedValue = Value(left.asInt() - right.asInt());
                return;
            }
            if (left.isNumber() && right.isNumber()) {
                lastEvaluatedValue = Value(left.asFloat() - right.asFloat());
                return;
            }
            throw MazException(expr.op.location, "Operands of '-' must be numbers.");
        }
        case TokenType::TOKEN_STAR: {
            if (left.isInt() && right.isInt()) {
                lastEvaluatedValue = Value(left.asInt() * right.asInt());
                return;
            }
            if (left.isNumber() && right.isNumber()) {
                lastEvaluatedValue = Value(left.asFloat() * right.asFloat());
                return;
            }
            throw MazException(expr.op.location, "Operands of '*' must be numbers.");
        }
        case TokenType::TOKEN_SLASH: {
            if (left.isNumber() && right.isNumber()) {
                double r = right.asFloat();
                if (r == 0.0) {
                    throw MazException(expr.op.location, "Division by zero.");
                }
                if (left.isInt() && right.isInt() && (left.asInt() % right.asInt() == 0)) {
                    lastEvaluatedValue = Value(left.asInt() / right.asInt());
                } else {
                    lastEvaluatedValue = Value(left.asFloat() / r);
                }
                return;
            }
            throw MazException(expr.op.location, "Operands of '/' must be numbers.");
        }
        case TokenType::TOKEN_PERCENT: {
            if (left.isInt() && right.isInt()) {
                int64_t r = right.asInt();
                if (r == 0) {
                    throw MazException(expr.op.location, "Modulo by zero.");
                }
                lastEvaluatedValue = Value(left.asInt() % r);
                return;
            }
            throw MazException(expr.op.location, "Operands of '%' must be integers.");
        }
        case TokenType::TOKEN_LESS: {
            if (left.isInt() && right.isInt()) {
                lastEvaluatedValue = Value::makeBool(left.asInt() < right.asInt());
            } else if (left.isNumber() && right.isNumber()) {
                lastEvaluatedValue = Value::makeBool(left.asFloat() < right.asFloat());
            } else if (left.isString() && right.isString()) {
                lastEvaluatedValue = Value::makeBool(left.asString() < right.asString());
            } else {
                throw MazException(expr.op.location, "Invalid operands for '<'.");
            }
            return;
        }
        case TokenType::TOKEN_LESS_EQUAL: {
            if (left.isInt() && right.isInt()) {
                lastEvaluatedValue = Value::makeBool(left.asInt() <= right.asInt());
            } else if (left.isNumber() && right.isNumber()) {
                lastEvaluatedValue = Value::makeBool(left.asFloat() <= right.asFloat());
            } else if (left.isString() && right.isString()) {
                lastEvaluatedValue = Value::makeBool(left.asString() <= right.asString());
            } else {
                throw MazException(expr.op.location, "Invalid operands for '<='.");
            }
            return;
        }
        case TokenType::TOKEN_GREATER: {
            if (left.isInt() && right.isInt()) {
                lastEvaluatedValue = Value::makeBool(left.asInt() > right.asInt());
            } else if (left.isNumber() && right.isNumber()) {
                lastEvaluatedValue = Value::makeBool(left.asFloat() > right.asFloat());
            } else if (left.isString() && right.isString()) {
                lastEvaluatedValue = Value::makeBool(left.asString() > right.asString());
            } else {
                throw MazException(expr.op.location, "Invalid operands for '>'.");
            }
            return;
        }
        case TokenType::TOKEN_GREATER_EQUAL: {
            if (left.isInt() && right.isInt()) {
                lastEvaluatedValue = Value::makeBool(left.asInt() >= right.asInt());
            } else if (left.isNumber() && right.isNumber()) {
                lastEvaluatedValue = Value::makeBool(left.asFloat() >= right.asFloat());
            } else if (left.isString() && right.isString()) {
                lastEvaluatedValue = Value::makeBool(left.asString() >= right.asString());
            } else {
                throw MazException(expr.op.location, "Invalid operands for '>='.");
            }
            return;
        }
        case TokenType::TOKEN_EQUAL_EQUAL: {
            if (left.type != right.type) {
                if (left.isNumber() && right.isNumber()) {
                    lastEvaluatedValue = Value::makeBool(left.asFloat() == right.asFloat());
                } else {
                    lastEvaluatedValue = Value::makeBool(false);
                }
            } else {
                switch (left.type) {
                    case ValueType::Null: lastEvaluatedValue = Value::makeBool(true); break;
                    case ValueType::Bool: lastEvaluatedValue = Value::makeBool(left.asBool() == right.asBool()); break;
                    case ValueType::Int: lastEvaluatedValue = Value::makeBool(left.asInt() == right.asInt()); break;
                    case ValueType::Float: lastEvaluatedValue = Value::makeBool(left.asFloat() == right.asFloat()); break;
                    case ValueType::String: lastEvaluatedValue = Value::makeBool(left.asString() == right.asString()); break;
                    default: lastEvaluatedValue = Value::makeBool(false); break;
                }
            }
            return;
        }
        case TokenType::TOKEN_BANG_EQUAL: {
            if (left.type != right.type) {
                if (left.isNumber() && right.isNumber()) {
                    lastEvaluatedValue = Value::makeBool(left.asFloat() != right.asFloat());
                } else {
                    lastEvaluatedValue = Value::makeBool(true);
                }
            } else {
                switch (left.type) {
                    case ValueType::Null: lastEvaluatedValue = Value::makeBool(false); break;
                    case ValueType::Bool: lastEvaluatedValue = Value::makeBool(left.asBool() != right.asBool()); break;
                    case ValueType::Int: lastEvaluatedValue = Value::makeBool(left.asInt() != right.asInt()); break;
                    case ValueType::Float: lastEvaluatedValue = Value::makeBool(left.asFloat() != right.asFloat()); break;
                    case ValueType::String: lastEvaluatedValue = Value::makeBool(left.asString() != right.asString()); break;
                    default: lastEvaluatedValue = Value::makeBool(true); break;
                }
            }
            return;
        }
        default:
            throw MazException(expr.op.location, "Unknown binary operator: '" + expr.op.lexeme + "'.");
    }
}

void Interpreter::visitUnaryExpr(UnaryExpr& expr) {
    Value right = evaluate(*expr.right);
    if (expr.op.type == TokenType::TOKEN_BANG) {
        lastEvaluatedValue = Value::makeBool(!right.isTruthy());
        return;
    }
    if (expr.op.type == TokenType::TOKEN_MINUS) {
        if (right.isInt()) {
            lastEvaluatedValue = Value(-right.asInt());
            return;
        }
        if (right.isFloat()) {
            lastEvaluatedValue = Value(-right.asFloat());
            return;
        }
        throw MazException(expr.op.location, "Unary '-' requires a numeric operand.");
    }
    throw MazException(expr.op.location, "Unknown unary operator: '" + expr.op.lexeme + "'.");
}

void Interpreter::visitCallExpr(CallExpr& expr) {
    Value callee = evaluate(*expr.callee);

    std::vector<Value> evaluatedArgs;
    for (const auto& arg : expr.arguments) {
        evaluatedArgs.push_back(evaluate(*arg));
    }

    if (callee.type == ValueType::NativeFunction) {
        lastEvaluatedValue = callee.asNativeFunction()(evaluatedArgs);
        return;
    }

    if (callee.type == ValueType::Function) {
        auto fn = callee.asFunction();

        // Check argument count against parameters
        size_t requiredParams = 0;
        for (const auto& p : fn->params) {
            if (!p.second) requiredParams++;
        }

        if (evaluatedArgs.size() < requiredParams || evaluatedArgs.size() > fn->params.size()) {
            throw MazException(expr.paren.location,
                "Function '" + fn->name + "' expected between " +
                std::to_string(requiredParams) + " and " +
                std::to_string(fn->params.size()) + " arguments, but got " +
                std::to_string(evaluatedArgs.size()) + ".");
        }

        auto fnEnv = std::make_shared<Environment>(fn->closure);

        for (size_t i = 0; i < fn->params.size(); ++i) {
            Value argVal;
            if (i < evaluatedArgs.size()) {
                argVal = evaluatedArgs[i];
            } else {
                // Evaluate default parameter expression in the function's closure environment
                std::shared_ptr<Environment> prev = currentEnv;
                currentEnv = fn->closure;
                argVal = evaluate(*fn->params[i].second);
                currentEnv = prev;
            }
            fnEnv->define(fn->params[i].first, argVal, false, false);
        }

        try {
            executeBlock(std::static_pointer_cast<BlockStmt>(fn->body)->statements, fnEnv);
            lastEvaluatedValue = Value::makeNull();
        } catch (const ReturnException& ret) {
            lastEvaluatedValue = ret.value;
        }
        return;
    }

    throw MazException(expr.paren.location, "Attempted to call a non-function value of type '" + callee.typeName() + "'.");
}

} // namespace maz
