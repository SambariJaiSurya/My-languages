#pragma once
#include <string>
#include <variant>
#include <vector>
#include <memory>
#include <functional>
#include <sstream>
#include <cmath>
#include <cstdint>

namespace maz {

class Environment;
class Expr;
class Stmt;

enum class ValueType {
    Null,
    Bool,
    Int,
    Float,
    String,
    Function,
    NativeFunction
};

struct Value;

using NativeFn = std::function<Value(const std::vector<Value>&)>;

struct MazFunction {
    std::string name;
    std::vector<std::pair<std::string, std::shared_ptr<Expr>>> params; // name and default expr
    std::shared_ptr<Stmt> body;
    std::shared_ptr<Environment> closure;
};

struct Value {
    ValueType type{ValueType::Null};
    std::variant<std::monostate, bool, int64_t, double, std::string, std::shared_ptr<MazFunction>, NativeFn> as;

    Value() : type(ValueType::Null), as(std::monostate{}) {}
    explicit Value(bool b) : type(ValueType::Bool), as(b) {}
    Value(int64_t i) : type(ValueType::Int), as(i) {}
    Value(int i) : type(ValueType::Int), as(static_cast<int64_t>(i)) {}
    Value(double d) : type(ValueType::Float), as(d) {}
    Value(std::string s) : type(ValueType::String), as(std::move(s)) {}
    Value(const char* s) : type(ValueType::String), as(std::string(s)) {}
    Value(std::shared_ptr<MazFunction> fn) : type(ValueType::Function), as(std::move(fn)) {}
    Value(NativeFn fn) : type(ValueType::NativeFunction), as(std::move(fn)) {}

    static Value makeNull() { return Value(); }
    static Value makeBool(bool b) { return Value(b); }

    bool isNull() const { return type == ValueType::Null; }
    bool isBool() const { return type == ValueType::Bool; }
    bool isInt() const { return type == ValueType::Int; }
    bool isFloat() const { return type == ValueType::Float; }
    bool isNumber() const { return isInt() || isFloat(); }
    bool isString() const { return type == ValueType::String; }
    bool isFunction() const { return type == ValueType::Function || type == ValueType::NativeFunction; }

    bool asBool() const { return std::get<bool>(as); }
    int64_t asInt() const { return std::get<int64_t>(as); }
    double asFloat() const {
        if (isInt()) return static_cast<double>(asInt());
        return std::get<double>(as);
    }
    const std::string& asString() const { return std::get<std::string>(as); }
    std::shared_ptr<MazFunction> asFunction() const { return std::get<std::shared_ptr<MazFunction>>(as); }
    NativeFn asNativeFunction() const { return std::get<NativeFn>(as); }

    std::string typeName() const {
        switch (type) {
            case ValueType::Null: return "null";
            case ValueType::Bool: return "bool";
            case ValueType::Int: return "int";
            case ValueType::Float: return "float";
            case ValueType::String: return "string";
            case ValueType::Function: return "function";
            case ValueType::NativeFunction: return "native_function";
            default: return "unknown";
        }
    }

    bool isTruthy() const {
        switch (type) {
            case ValueType::Null: return false;
            case ValueType::Bool: return asBool();
            case ValueType::Int: return asInt() != 0;
            case ValueType::Float: return asFloat() != 0.0;
            case ValueType::String: return !asString().empty();
            default: return true;
        }
    }

    std::string toString() const {
        switch (type) {
            case ValueType::Null: return "null";
            case ValueType::Bool: return asBool() ? "true" : "false";
            case ValueType::Int: return std::to_string(asInt());
            case ValueType::Float: {
                std::ostringstream ss;
                ss << asFloat();
                std::string s = ss.str();
                if (s.find('.') == std::string::npos && s.find('e') == std::string::npos) {
                    s += ".0";
                }
                return s;
            }
            case ValueType::String: return asString();
            case ValueType::Function: return "<function " + asFunction()->name + ">";
            case ValueType::NativeFunction: return "<native_function>";
            default: return "<value>";
        }
    }
};

} // namespace maz
