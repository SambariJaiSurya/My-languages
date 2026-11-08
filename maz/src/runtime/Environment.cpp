#include "Environment.hpp"

namespace maz {

Environment::Environment(std::shared_ptr<Environment> p) : parent(std::move(p)) {}

void Environment::define(const std::string& name, Value value, bool isConst, bool isDyn, bool isInitialized, ValueType explicitType) {
    Symbol sym;
    sym.value = value;
    sym.fixedType = (explicitType != ValueType::Null) ? explicitType : value.type;
    sym.isConst = isConst;
    sym.isDyn = isDyn;
    sym.isInitialized = isInitialized;
    values[name] = sym;
}

void Environment::markGlobal(const std::string& name) {
    globalBindings.insert(name);
}

bool Environment::isMarkedGlobal(const std::string& name) const {
    if (globalBindings.find(name) != globalBindings.end()) return true;
    if (parent) return parent->isMarkedGlobal(name);
    return false;
}

bool Environment::existsCurrentScope(const std::string& name) const {
    return values.find(name) != values.end();
}

void Environment::assign(const Token& name, Value value, bool isForce) {
    if (isMarkedGlobal(name.lexeme) && parent) {
        getGlobal()->assign(name, std::move(value), isForce);
        return;
    }

    auto it = values.find(name.lexeme);
    if (it != values.end()) {
        if (it->second.isConst && it->second.isInitialized) {
            throw MazException(name.location, "Error: Cannot modify a constant variable '" + name.lexeme + "'.");
        }
        if (!it->second.isDyn && !isForce) {
            if (it->second.fixedType != ValueType::Null && it->second.fixedType != value.type) {
                // Allow int to float if converting
                if (it->second.fixedType == ValueType::Float && value.isInt()) {
                    value = Value(static_cast<double>(value.asInt()));
                } else {
                    std::string expectedName = "variable";
                    if (it->second.fixedType == ValueType::Int) expectedName = "an integer";
                    else if (it->second.fixedType == ValueType::Float) expectedName = "a float";
                    else if (it->second.fixedType == ValueType::String) expectedName = "a string";
                    else if (it->second.fixedType == ValueType::Bool) expectedName = "a boolean";

                    throw MazException(name.location,
                        "Type Error: Cannot assign " + value.typeName() + " to " + expectedName + " variable '" + name.lexeme + "'.");
                }
            }
        }
        if (isForce) {
            it->second.fixedType = value.type;
        }
        it->second.value = std::move(value);
        it->second.isInitialized = true;
        return;
    }

    if (parent) {
        parent->assign(name, std::move(value), isForce);
        return;
    }

    // Inferred definition at global/current scope
    define(name.lexeme, std::move(value), false, false, true);
}

void Environment::assignOrDeclareGlobal(const Token& name, Value value) {
    if (exists(name.lexeme)) {
        assign(name, std::move(value), false);
    } else {
        getGlobal()->define(name.lexeme, std::move(value), false, false, true);
    }
}

Value Environment::get(const Token& name) {
    if (isMarkedGlobal(name.lexeme) && parent) {
        return getGlobal()->get(name);
    }

    auto it = values.find(name.lexeme);
    if (it != values.end()) {
        if (!it->second.isInitialized) {
            throw MazException(name.location, "Error: Variable '" + name.lexeme + "' may be uninitialized.");
        }
        return it->second.value;
    }

    if (parent) {
        return parent->get(name);
    }

    throw MazException(name.location, "Undefined variable '" + name.lexeme + "'.");
}

bool Environment::exists(const std::string& name) const {
    if (values.find(name) != values.end()) return true;
    if (parent) return parent->exists(name);
    return false;
}

std::shared_ptr<Environment> Environment::getGlobal() {
    auto cur = shared_from_this();
    while (cur->parent) {
        cur = cur->parent;
    }
    return cur;
}

} // namespace maz

