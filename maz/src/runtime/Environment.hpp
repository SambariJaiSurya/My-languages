#pragma once
#include "../common/Value.hpp"
#include "../common/Token.hpp"
#include "../common/Error.hpp"
#include <unordered_map>
#include <memory>
#include <string>

#include <unordered_set>

namespace maz {

struct Symbol {
    Value value;
    ValueType fixedType;
    bool isConst{false};
    bool isDyn{false};
    bool isInitialized{false};
};

class Environment : public std::enable_shared_from_this<Environment> {
public:
    explicit Environment(std::shared_ptr<Environment> parent = nullptr);

    void define(const std::string& name, Value value, bool isConst = false, bool isDyn = false, bool isInitialized = true, ValueType explicitType = ValueType::Null);
    void assign(const Token& name, Value value, bool isForce = false);
    void assignOrDeclareGlobal(const Token& name, Value value);
    void markGlobal(const std::string& name);
    bool isMarkedGlobal(const std::string& name) const;
    Value get(const Token& name);
    bool exists(const std::string& name) const;
    bool existsCurrentScope(const std::string& name) const;
    std::shared_ptr<Environment> getGlobal();

    std::shared_ptr<Environment> getParent() const { return parent; }

private:
    std::shared_ptr<Environment> parent;
    std::unordered_map<std::string, Symbol> values;
    std::unordered_set<std::string> globalBindings;
};

} // namespace maz

