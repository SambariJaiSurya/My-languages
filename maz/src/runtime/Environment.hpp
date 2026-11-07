#pragma once
#include "../common/Value.hpp"
#include "../common/Token.hpp"
#include "../common/Error.hpp"
#include <unordered_map>
#include <memory>
#include <string>

namespace maz {

struct Symbol {
    Value value;
    ValueType fixedType;
    bool isConst{false};
    bool isDyn{false};
};

class Environment : public std::enable_shared_from_this<Environment> {
public:
    explicit Environment(std::shared_ptr<Environment> parent = nullptr);

    void define(const std::string& name, Value value, bool isConst = false, bool isDyn = false);
    void assign(const Token& name, Value value, bool isForce = false);
    void assignOrDeclareGlobal(const Token& name, Value value);
    Value get(const Token& name);
    bool exists(const std::string& name) const;
    std::shared_ptr<Environment> getGlobal();

    std::shared_ptr<Environment> getParent() const { return parent; }

private:
    std::shared_ptr<Environment> parent;
    std::unordered_map<std::string, Symbol> values;
};

} // namespace maz

