# MAZ Language Specification
**Version:** 0.1.0-draft  
**Status:** Living Specification  
**Author:** MAZ Language Design Group  

---

## 1. Introduction

MAZ is an evolving, general-purpose, multiparadigm programming language engineered for cross-domain versatility. The language bridges the gap between high-level expressive productivity (akin to Python and modern JavaScript) and low-level performance, safety, and hardware control (akin to C++ and Rust).

This specification is a **living document**. It defines the formal syntax, semantics, type system, standard libraries, and operational behavior of MAZ. As the creator's programming journey progresses, MAZ will be iteratively refined, extended, and upgraded.

---

## 2. Lexical Structure

### 2.1 Character Set & Encoding
MAZ source files are encoded in UTF-8.

### 2.2 Semicolons & Statement Delimitation
MAZ is a **semicolon-free** language. Statements are terminated by:
1. Newlines (`\n`) that follow a complete grammatical statement.
2. Closing curly braces (`}`).
3. End-of-file (`EOF`).

Explicit semicolons (`;`) are permitted as optional statement separators, but are idiomatic to omit.

### 2.3 Comments
MAZ supports two types of comments:
- **Single-line comments:** `// ...` (runs until end-of-line)
- **Multi-line comments:** `/* ... */` (can span multiple lines; nesting is supported in future versions)
- **Documentation comments:** `///` and `/** ... */` for documentation generation tools.

### 2.4 Identifiers
Identifiers start with an ASCII letter (`a-z`, `A-Z`) or underscore (`_`), followed by any number of letters, digits (`0-9`), or underscores.

### 2.5 Keywords
The reserved keywords of MAZ include:
```
def, return, const, dyn, force, new, if, else, for, while,
try, catch, class, struct, constructor, extends, include, implement,
public, private, protected, internal, async, await, use, true, false, null
```

---

## 3. Type System & Variables

MAZ utilizes a **hybrid type system** combining automatic static type inference, optional explicit typing, dynamic typing via `dyn`, and explicit type mutation via `force`.

### 3.1 Primitive Types
- `int`: 64-bit signed integer.
- `float`: 64-bit IEEE 754 floating-point number.
- `string`: UTF-8 encoded text sequence.
- `bool`: Boolean value (`true` or `false`).
- `null`: Absence of value.

### 3.2 Variable Declaration & Inference (Rules 1, 4, 45)
Variables are declared without mandatory introductory keywords like `let` or `var`:
```maz
x = 42              // Inferred as int
name = "Antigravity" // Inferred as string
rate = 3.14         // Inferred as float
active = true       // Inferred as bool
```

Optional explicit types are supported:
```maz
int count = 10
string title = "MAZ Project"
```

### 3.3 Dynamic Variables: `dyn` (Rule 9, 23)
When a variable is declared with `dyn`, it opts out of rigid static type enforcement and may hold values of different types at runtime:
```maz
dyn item = 100
item = "one hundred"  // Allowed: item is dynamic
```

### 3.4 Explicit Type-Changing Assignment: `force` (Rule 9)
In MAZ, an ordinary variable declared by inference or explicit type cannot be reassigned to a different type. Attempting to assign a value of an incompatible type raises a compile/runtime type error:
```maz
x = 10
x = "text"           // Error: Cannot assign string to variable of type int
```
To explicitly permit changing the type of an otherwise statically-typed variable, the `force` keyword is used:
```maz
x = 10
force x = "text"     // Allowed: force rebinds the variable with new type string
```

### 3.5 Constants: `const` (Rule 1)
Constants are immutable bindings that cannot be reassigned once initialized:
```maz
const PI = 3.141592653589793
const APP_NAME = "MAZ Engine"
```

### 3.6 Nullable Types: `?` (Rules 62, 71)
By default, variables are non-nullable. Only variables explicitly declared with a nullable modifier `?` can hold `null`:
```maz
string? optionalName = null
optionalName = "Alice"

string nonNullName = "Bob"
nonNullName = null   // Error: nonNullName cannot accept null
```

---

## 4. Expressions & Operators

### 4.1 Arithmetic Operators (Rule 13)
- `+`: Addition and string concatenation
- `-`: Subtraction and unary negation
- `*`: Multiplication
- `/`: Division (floating-point division if operands or result requires float)
- `%`: Modulo (remainder)

### 4.2 Increment and Decrement (Rule 51)
- `++`: Pre- and post-increment
- `--`: Pre- and post-decrement

### 4.3 Comparison & Logical Operators
- `==`, `!=`: Equality and inequality
- `<`, `<=`, `>`, `>=`: Relational comparisons
- `&&`: Logical AND (short-circuiting)
- `||`: Logical OR (short-circuiting)
- `!`: Logical NOT

### 4.4 Strings (Rules 15, 26)
Strings are delimited by double quotes `"..."`.
String concatenation uses `+`:
```maz
greeting = "Hello, " + name + "!"
```
Multiline strings are supported using triple-quote syntax `"""..."""` or escaped newlines.

---

## 5. Control Flow

### 5.1 Blocks (Rule 2)
Blocks are delimited by curly braces `{}` and establish lexical scopes.

### 5.2 Conditional Statements (Rule 6)
C++ style conditions with parentheses and curly braces:
```maz
if (score >= 90) {
    display("Grade: A")
} else if (score >= 80) {
    display("Grade: B")
} else {
    display("Grade: C")
}
```

### 5.3 Loops (Rule 7, 24)

#### Three-Part Loop with Commas (Rule 7)
MAZ uses C++-style three-part loops, with clauses separated by **commas** instead of semicolons:
```maz
for (new i = 0, i < 10, i++) {
    display(i)
}
```
**Semantics of `new` in loops:**
- `new` creates a loop-local variable that shadows any outer variable of the same name.
- The loop-local variable goes out of scope when the loop exits.
- Without `new`, an existing variable in outer scope is reused and modified. If no variable exists in outer scope, it binds to the enclosing scope.

#### While Loops
```maz
count = 0
while (count < 5) {
    display(count)
    count++
}
```

#### Collection Iteration (Rule 24)
C++-style collection iteration using a colon `:`:
```maz
numbers = [10, 20, 30]
for (n : numbers) {
    display(n)
}
```

---

## 6. Functions (Rules 3, 21, 22, 63)

### 6.1 Function Definition
Functions are declared using `def`. Return types are inferred automatically:
```maz
def add(a, b) {
    return a + b
}
```

### 6.2 Default Parameters (Rule 22)
Parameters can specify default values. When an argument without a default value is omitted at call site, a compiler/runtime error is raised:
```maz
def greet(name = "Developer", prefix = "Welcome") {
    display(prefix + ", " + name + "!")
}

greet()                 // Outputs: Welcome, Developer!
greet("Alice")          // Outputs: Welcome, Alice!
greet("Bob", "Hello")   // Outputs: Hello, Bob!
```

### 6.3 No Function Overloading (Rule 63)
In MAZ initial design, traditional function overloading (multiple functions sharing the same name with differing signatures) is not permitted. Default parameters and variable arguments handle variadic use cases.

### 6.4 Asynchronous Functions: `async` & `await` (Rule 19, 30)
```maz
async def fetchData(url) {
    response = await httpGet(url)
    return response.body
}
```

---

## 7. Standard I/O (Rules 5, 73)

### 7.1 Standard Output (Rule 5)
Standard output is printed using the built-in `display()` function:
```maz
display("Hello, MAZ World!")
display(10 + 20)
```

### 7.2 MAZ Input System (Rule 73)
MAZ provides five built-in input functions directly in the terminal without external libraries. C++-style `cin >>` syntax is prohibited.

1. **`input(prompt?)` — Universal input:**
   - Accepts any user-entered text.
   - Returns a string by default.
   - Does not reject input based on its contents.
2. **`inputInt(prompt?)` — Integer input:**
   - Accepts valid integers only.
   - Returns an integer.
   - Throws a clear runtime error if the user enters a non-integer, decimal, or invalid value.
3. **`inputFloat(prompt?)` — Floating-point input:**
   - Accepts valid floating-point numbers.
   - Returns a float.
   - Throws an error for invalid input.
4. **`inputBool(prompt?)` — Boolean input:**
   - Accepts Boolean values (`true` or `false`, case-insensitive).
   - Returns a Boolean.
   - Throws an error for invalid input.
5. **`inputString(prompt?)` — String input:**
   - Accepts text.
   - Returns a string without numeric or boolean conversions.

#### Example Usage
```maz
name = inputString("Enter your name: ")
age = inputInt("Enter your age: ")
height = inputFloat("Enter your height: ")
isStudent = inputBool("Are you a student? ")
data = input("Enter anything: ")
```

---

## 8. Error Handling (Rules 8, 60)

Errors are handled using `try` and `catch` blocks:
```maz
try {
    result = 10 / 0
} catch (err) {
    display("Caught an error: " + err.message)
}
```
Unhandled errors immediately halt execution and generate comprehensive diagnostic reports, including file name, line number, column number, and execution stack trace.

---

## 9. Object-Oriented Programming (Rules 11, 17, 18, 20, 49, 50, 69, 70)

### 9.1 Classes & Structures
- `class`: Reference-type object blueprint with encapsulation, inheritance, and polymorphism.
- `struct`: Value-type lightweight container for grouped data fields.

### 9.2 Constructors (Rule 69)
Constructors are explicitly declared with the `constructor` keyword:
```maz
class Point {
    public x
    public y

    constructor(x, y) {
        this.x = x
        this.y = y
    }

    def distance() {
        return Math.sqrt(this.x * this.x + this.y * this.y)
    }
}
```

### 9.3 Access Modifiers (Rules 11, 20)
- `public`: Accessible from any scope.
- `private`: Accessible only within the declaring class.
- `protected`: Accessible within the declaring class and derived subclasses.
- `internal`: Accessible within the same package or module.

### 9.4 Inheritance & Composition: `extends` vs `include` (Rules 18, 70)
- `extends`: Classical single-inheritance hierarchy (subtyping / polymorphism).
- `include`: Mixin and composition mechanism for injecting behavior and reusable methods without inheritance coupling.

### 9.5 Interfaces: `implement` (Rule 50)
```maz
interface Drawable {
    def draw()
}

class Circle implement Drawable {
    def draw() {
        display("Drawing a circle")
    }
}
```

---

## 10. Memory Management & Systems Programming (Rules 25, 47, 65, 72)

1. **Automatic Garbage Collection (Default):** Memory allocated for high-level objects, strings, arrays, and closures is managed automatically by a tracing/reference-counting garbage collector.
2. **Explicit Ownership & Manual Allocation:** Systems developers can opt into manual allocation, stack allocation, or deterministic ownership scopes for high-performance and embedded targets (e.g. Arduino, ESP32).
3. **Pointers & References:** Low-level pointer syntax (`*`, `&`) is permitted in designated systems code with clear compiler safety boundaries.

---

## 11. Modules & Imports (Rules 12, 28)

Modules are imported using the `use` keyword:
```maz
use maz.math
use maz.network.http
use maz.arduino as arduino
```

---

## 12. Versioning & Evolution Principles

Every release of MAZ updates this specification. Future changes must maintain backwards compatibility where possible, document breaking changes in `CHANGELOG.md`, and record the underlying architectural rationale in `DECISIONS.md`.

