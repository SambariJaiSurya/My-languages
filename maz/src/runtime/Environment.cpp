#include "Environment.hpp"

namespace maz {

Environment::Environment(std::shared_ptr<Environment> p) : parent(std::move(p)) {}

void Environment::define(const std::string& name, Value value, bool isConst, bool isDyn) {
    Symbol sym;
    sym.value = value;
    sym.fixedType = value.type;
    sym.isConst = isConst;
    sym.isDyn = isDyn;
    values[name] = sym;
}

void Environment::assign(const Token& name, Value value, bool isForce) {
    auto it = values.find(name.lexeme);
    if (it != values.end()) {
        if (it->second.isConst) {
            throw MazException(name.location, "Cannot reassign constant '" + name.lexeme + "'.");
        }
        if (!it->second.isDyn && !isForce) {
            if (it->second.fixedType != value.type) {
                // Allow int to float or vice versa if numbers, but flag incompatible types
                if (it->second.fixedType == ValueType::Float && value.isInt()) {
                    value = Value(static_cast<double>(value.asInt()));
                } else {
                    throw MazException(name.location,
                        "Type mismatch: cannot assign value of type '" + value.typeName() +
                        "' to variable '" + name.lexeme + "' of type '" +
                        it->second.value.typeName() + "'. Use 'force " + name.lexeme +
                        " = ...' or declare as 'dyn'.");
                }
            }
        }
        if (isForce) {
            it->second.fixedType = value.type;
        }
        it->second.value = std::move(value);
        return;
    }

    if (parent) {
        parent->assign(name, std::move(value), isForce);
        return;
    }

    // Implicit definition if assigning to a new identifier at current scope
    define(name.lexeme, std::move(value), false, false);
}

void Environment::assignOrDeclareGlobal(const Token& name, Value value) {
    if (exists(name.lexeme)) {
        assign(name, std::move(value), false);
    } else {
        getGlobal()->define(name.lexeme, std::move(value), false, false);
    }
}

Value Environment::get(const Token& name) {
    auto it = values.find(name.lexeme);
    if (it != values.end()) {
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

