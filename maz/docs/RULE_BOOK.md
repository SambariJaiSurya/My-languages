# The MAZ Language Rule Book: Rules 1 to 87 With Examples

Welcome to the definitive **MAZ Rule Book**. This document covers every single rule from **Rule 1 to Rule 87**, providing a clear explanation and practical MAZ code example for each rule.

---

# Part 1: Core Syntax & Types (Rules 1–10)

### Rule 1: Assignment & Type Inference
Variables are created via assignment. Types are inferred on initial assignment without requiring explicit type keywords.
```maz
x = 10              // Inferred as int
name = "Surya"      // Inferred as string
isReady = true      // Inferred as bool
```

### Rule 2: Curly Braces `{}` for Blocks
Code blocks are always demarcated with curly braces `{}` rather than indentation or `begin`/`end`.
```maz
if (x > 5) {
    display("x is greater than 5")
}
```

### Rule 3: Functions with `def`
Functions are declared using the `def` keyword. Return types are inferred automatically.
```maz
def add(a, b) {
    return a + b
}
```

### Rule 4: Hybrid Type System
Combines automatic inference, static type locking on variables, `dyn` dynamic types, and `force` re-typing.
```maz
val = 42            // Inferred int
// val = "text"     // Error: cannot assign string to int
```

### Rule 5: Standard Output with `display()`
Output is printed using the built-in `display()` function without requiring imports.
```maz
display("Hello, MAZ World!")
display("Score:", 100)
```

### Rule 6: C++ Style Conditions
Conditionals use `if (...) { ... } else if (...) { ... } else { ... }`.
```maz
if (score >= 90) {
    display("Grade A")
} else if (score >= 75) {
    display("Grade B")
} else {
    display("Keep practicing")
}
```

### Rule 7: Three-Part Loop with Commas & `new`
Loops use commas `,` as clause separators (no semicolons). `new` scopes a variable locally to the loop.
```maz
for (new i = 0, i < 5, i++) {
    display("i is:", i)
}
// i is not accessible here
```

### Rule 8: Structured Error Handling (`try` / `catch`)
Exceptions are caught safely using structured `try` and `catch`.
```maz
try {
    result = 10 / 0
} catch (err) {
    display("Caught error:", err)
}
```

### Rule 9: Dynamic Types (`dyn`) & Explicit Re-typing (`force`)
`dyn` allows a variable to hold any type dynamically. `force` explicitly overrides an inferred type.
```maz
dyn flexible = 100
flexible = "Now I am text"     // Valid with dyn

counter = 10
force counter = "ten"          // Explicitly changes static type
```

### Rule 10: Array Literals & Methods
Arrays use square brackets `[ ... ]` with standard methods like `.push()`.
```maz
items = [10, 20, 30]
items.push(40)
display("Total items:", items.length())
```

---

# Part 2: Object-Oriented Programming & Modularity (Rules 11–20)

### Rule 11: Classes & Access Modifiers
Classes support `public`, `private`, `protected`, and `internal`.
```maz
class BankAccount {
    private balance = 0

    public def deposit(amount) {
        this.balance += amount
    }
}
```

### Rule 12: Module Imports with `use`
External files and libraries are imported using `use`.
```maz
use maz.math
use sys
```

### Rule 13: Arithmetic Operators
Supports `+`, `-`, `*`, `/`, `%`.
```maz
sum = 10 + 5
remainder = 14 % 3
```

### Rule 14: Standard Literals
Lowercase `true`, `false`, and `null`.
```maz
flag = true
emptyVal = null
```

### Rule 15: Strings & Concatenation
Double-quoted strings concatenated using `+`.
```maz
greeting = "Hello, " + "MAZ!"
```

### Rule 16: Comments
Single-line `//` and block `/* ... */`.
```maz
// This is a single-line comment
/* This is a 
   multi-line comment */
```

### Rule 17: Typed & Inferred Object Instantiation
Classes can be instantiated cleanly.
```maz
acc = BankAccount()
```

### Rule 18: Inheritance (`extends`) vs Mixins (`include`)
Single inheritance with `extends`; reusable traits with `include`.
```maz
class Animal {
    def speak() { display("Sound") }
}

class Dog extends Animal {
    def bark() { display("Woof!") }
}
```

### Rule 19: Asynchronous Functions (`async` / `await`)
Built-in async semantics for non-blocking I/O.
```maz
async def fetchWebData(url) {
    res = await httpGet(url)
    return res
}
```

### Rule 20: Granular Encapsulation
Private fields are never accessible outside their declaring class.
```maz
class Secret {
    private code = 1234
}
```

---

# Part 3: Functions, Systems & Concurrency (Rules 21–35)

### Rule 21: Inferred Return Types
Functions automatically determine their return type without redundant headers.
```maz
def multiply(a, b) {
    return a * b    // Inferred return type: int or float
}
```

### Rule 22: Default Parameters
Parameters can have default values. Missing non-default parameters raise an error.
```maz
def greet(name = "User", prefix = "Welcome") {
    display(prefix + ", " + name)
}
greet()             // Welcome, User
greet("Surya")      // Welcome, Surya
```

### Rule 23: Homogeneous & Heterogeneous Arrays
Homogeneous by default; `dyn` arrays for mixed types.
```maz
numbers = [1, 2, 3]               // int array
dyn mixed = [1, "two", true]     // dynamic mixed array
```

### Rule 24: Collection Iteration (`for item : collection`)
Iterate over arrays and collections cleanly.
```maz
fruits = ["apple", "banana", "cherry"]
for (fruit : fruits) {
    display(fruit)
}
```

### Rule 25: Pointers & Address-Of (`*`, `&`)
Low-level memory addresses for microcontroller and systems code.
```maz
val = 100
ptr = &val
display(*ptr)       // Dereference pointer
```

### Rule 26: Multi-line String Literals
Strings can span multiple lines without concatenation.
```maz
query = "SELECT id, name
FROM users
WHERE active = true"
```

### Rule 27: First-Class Functions
Functions can be stored in variables and passed into other functions.
```maz
def doubleVal(x) { return x * 2 }
op = doubleVal
display(op(10))     // 20
```

### Rule 28: Hierarchical Modules
Namespaces organized in dots.
```maz
use maz.hardware.gpio
```

### Rule 29: Parametric Generics
Simplified generic functions and collections.
```maz
def identity<T>(value) {
    return value
}
```

### Rule 30: Native Threads & Tasks
Parallel CPU execution alongside asynchronous event loops.
```maz
spawn(() => {
    display("Running in background thread")
})
```

### Rule 31: Built-in File I/O
Core runtime support for reading and writing files.
```maz
file = File("notes.txt")
file.writeAllText("MAZ rule book")
```

### Rule 32: High-Level & Low-Level Bridge
Use high-level syntax for apps, or low-level pointers for embedded devices.

### Rule 33: MAZ Web Frontend
Native compilation to WebAssembly/HTML DOM components.

### Rule 34: Built-in HTTP Server
Core web networking capabilities.
```maz
use maz.network.http
```

### Rule 35: Embedded Database Engine
Integrated key-value and tabular storage drivers.

---

# Part 4: Compiler, Tooling & Advanced Features (Rules 36–55)

### Rule 36: JavaScript & Browser Interop
Interop bindings for browser runtime environments.

### Rule 37: Dual Engine: Bytecode VM & Native Compilation
Fast development cycle via VM, release builds via native compiler.

### Rule 38: Just-In-Time (JIT) Optimization
Hot loops in the VM are dynamically compiled to machine code.

### Rule 39: Integrated Package Manager
Install libraries with `maz install <package>`.

### Rule 40: Interactive Debugger
Built-in CLI stepping, breakpoints, and state inspection.

### Rule 41: GPU Compute & Graphics (`maz.gpu`)
Direct access to compute shaders and rendering pipelines.

### Rule 42: Game Development Engine (`maz.game`)
Built-in 2D physics and instant scene resets.

### Rule 43: Machine Learning & Tensors (`maz.ai`, `maz.ml`)
Native tensors and auto-differentiation in standard library.

### Rule 44: Direct Microcontroller Programming (Arduino/ESP32)
Zero-dependency GPIO and hardware registers:
```maz
pinMode(13, OUTPUT)
digitalWrite(13, HIGH)
delay(1000)
```

### Rule 45: Explicit Types When Desired
Optional explicit type annotation alongside inference:
```maz
int count = 5
string name = "Surya"
```

### Rule 46: Enumerations (`enum`)
Strongly-typed named states.
```maz
enum Status {
    Pending,
    Active,
    Done
}
```

### Rule 47: Hybrid Memory Allocation
Automatic Garbage Collection by default, with manual `alloc()`/`free()` for systems code.

### Rule 48: Reflection & Type Inspection (`typeOf`)
Runtime inspection of variable types:
```maz
x = 42
display(typeOf(x))  // "int"
```

### Rule 49: Value `struct` vs Reference `class`
`struct` allocates on the stack for high speed; `class` on the heap with references.
```maz
struct Point {
    x = 0
    y = 0
}
```

### Rule 50: Interfaces (`interface` & `implement`)
Polymorphic interface contracts.
```maz
interface Drawable {
    def draw()
}
class Circle implement Drawable {
    def draw() { display("Drawing circle") }
}
```

### Rule 51: Increment & Decrement (`++`, `--`)
Concise mutation operators:
```maz
count = 0
count++
display(count)      // 1
```

### Rule 52: Unified CLI (`maz`)
Single tool: `maz run`, `maz build`, `maz test`, `maz fmt`.

### Rule 53: Built-in Automated Test Runner
Run automated tests with `maz test`.

### Rule 54: Automated Documentation Generator
Generates HTML docs from `///` doc comments.

### Rule 55: Native Graphical User Interface (`maz.gui`)
Declarative windowing and UI components.

---

# Part 5: Language Integrity & Architecture (Rules 56–72)

### Rule 56: Multiplatform Portability
Runs across Windows, Linux, macOS, Android, and embedded targets.

### Rule 57: Single-File Scripts & Multi-file Packages
Run standalone scripts without creating project configurations.

### Rule 58: Hygienic Metaprogramming Macros
Compile-time code generation without syntax pollution.

### Rule 59: Controlled Custom Domain-Specific Syntax (DSLs)

### Rule 60: Actionable Diagnostic Error Traces
Errors display line number, column, code snippet, and caret pointers.

### Rule 61: Interactive REPL
Launch instant shell with `maz repl`.

### Rule 62: Safe Non-Nullable Types by Default
Types cannot hold `null` unless marked with `?`.
```maz
name = "Surya"      // Cannot be null
name? maybeName = null // Nullable
```

### Rule 63: No Function Overloading in Initial Specification
Prevents signature ambiguities; handled via default & variadic params.

### Rule 64: Foreign Function Interface (FFI)
Call C and C++ libraries directly.

### Rule 65: Tracing GC for General Applications
Automatic memory reclamation for classes and closures.

### Rule 66: Compile-Time Constant Execution (`comptime`)
Evaluate expressions at compile time for zero runtime overhead.

### Rule 67: Sandboxed Secure Defaults
File and network operations require explicit permissions when sandboxed.

### Rule 68: Standalone Native Binary Distribution
Compile self-contained executables that run without installing MAZ.

### Rule 69: Explicit `constructor` Keyword
Constructors use `constructor` instead of class name.
```maz
class Person {
    constructor(name) {
        this.name = name
    }
}
```

### Rule 70: Formal Separation of `extends` and `include`
`extends` = Single class inheritance hierarchy.  
`include` = Multi-mixin behavioral composition.

### Rule 71: Nullable Syntax Modifier `?`
Compact modifier for optional values:
```maz
int? score = null
```

### Rule 72: Coherent Ownership Model
Prevents GC from moving or reclaiming objects held by raw pointers.

---

# Part 6: The Standard Input System (Rule 73)

### Rule 73: MAZ Input System
Five built-in terminal input functions without external dependencies or C++ `cin >>` syntax.

#### 1. Universal Input: `input()`
```maz
data = input("Enter anything: ")
display("You entered:", data)
```

#### 2. Strict Integer Input: `inputint()`
```maz
age = inputint("Enter your age: ")
display("In 5 years:", age + 5)
```

#### 3. Strict Floating-Point Input: `inputfloat()`
```maz
height = inputfloat("Enter your height: ")
display("Height:", height)
```

#### 4. Strict Boolean Input: `inputbool()`
Accepts `"true"` or `"false"` (case-insensitive); throws error otherwise.
```maz
isStudent = inputbool("Are you a student? ")
if (isStudent) {
    display("Student Discount Applied")
}
```

#### 5. Strict String Input: `inputstring()`
```maz
name = inputstring("Enter your full name: ")
display("Hello,", name)
```

---

# Part 7: Advanced Operations Specification (Rules 74–87)

### Rule 74: Operators & Expressions
- **Compound Assignment:** `+=`, `-=`, `*=`, `/=`, `%=`
  ```maz
  score = 100
  score += 10
  display(score)    // 110
  ```
- **Word & Symbol Logic:** Both `&&`/`and`, `||`/`or`, `!`/`not` supported.
  ```maz
  if (age >= 18 and hasLicense) {
      display("Can drive")
  }
  ```
- **Ternary Operator:** `condition ? trueVal : falseVal`
  ```maz
  status = score >= 50 ? "Pass" : "Fail"
  ```
- **Type Conversions:** Standalone and dot methods.
  ```maz
  n1 = toInt("100")
  n2 = "100".toInt()
  s = toString(100)
  ```

### Rule 75: Conditions & Control Flow
- **Break & Continue:**
  ```maz
  for (new i = 0, i < 10, i++) {
      if (i == 3) continue
      if (i == 7) break
      display(i)
  }
  ```
- **Switch with Auto-Break:**
  ```maz
  switch (day) {
      case 1:
          display("Monday")
      case 2:
          display("Tuesday")
          fallthrough
      default:
          display("Other")
  }
  ```

### Rule 76: Variables & Scope
- **Strict Block Scoping:** Variables in `{}` never leak out.
- **Explicit Global Rebinding:**
  ```maz
  counter = 0
  def increment() {
      global counter
      counter += 1
  }
  ```

### Rule 77: Advanced Functions
- **Lambdas & Arrow Functions:**
  ```maz
  sq = (x) => x * x
  sum = (a, b) => { return a + b }
  ```
- **Named Arguments:**
  ```maz
  greet(name: "Surya", prefix: "Welcome")
  ```
- **Variadic Arguments (`...args`):**
  ```maz
  def total(...numbers) {
      t = 0
      for (n : numbers) { t += n }
      return t
  }
  ```

### Rule 78: Strings & Characters
- **Interpolation with `${}`:**
  ```maz
  name = "Surya"
  display("Hello, ${name}! In 5 years: ${age + 5}")
  ```
- **Dedicated `char` Type:**
  ```maz
  char initial = 'S'
  string title = "MAZ"
  ```

### Rule 79: Arrays & Collections
- **Bracket Literals & Methods:**
  ```maz
  nums = [10, 20, 30]
  nums.push(40)
  nums.pop()
  display(nums.length())
  ```
- **Maps / Dictionaries:**
  ```maz
  user = { "name": "Surya", "age": 15 }
  display(user["name"])
  ```

### Rule 80: Advanced OOP
- **Destructors:**
  ```maz
  class Resource {
      destructor() {
          display("Resource cleaned up")
      }
  }
  ```
- **Properties (`get` and `set`):**
  ```maz
  class Box {
      private _w = 10
      get width() { return this._w }
      set width(v) { if (v > 0) this._w = v }
  }
  ```

### Rule 81: Advanced Error Handling
- **Multi-catch & `finally`:**
  ```maz
  try {
      val = toInt("abc")
  } catch (err: TypeError) {
      display("Type error caught")
  } finally {
      display("Cleanup completed")
  }
  ```

### Rule 82: Modules & Packages
- **Selective Import & Export:**
  ```maz
  // In math.maz
  export def add(a, b) { return a + b }

  // In main.maz
  use math { add }
  use math as m
  ```

### Rule 83: Systems Memory Management
- **Manual Allocation:**
  ```maz
  ptr = alloc<int>(10)
  ptr[0] = 42
  free(ptr)
  ```

### Rule 84: Native Concurrency
- **Spawning & Channels:**
  ```maz
  ch = Channel()
  spawn(() => {
      ch.send("Hello from worker task")
  })
  msg = ch.receive()
  display(msg)
  ```

### Rule 85: System Operations & File System
- **Sys Module & Files:**
  ```maz
  use sys
  display(sys.args)
  displayErr("Error stream")

  file = File("data.txt")
  if (file.exists()) {
      display(file.readAllText())
  }
  ```

### Rule 86: Compiler & Tooling
- **Unified Tool Commands:**
  ```bash
  maz create MyProject
  maz run main.maz
  maz build main.maz --release
  maz test
  maz fmt
  ```

### Rule 87: Security & Portability
- **Sandboxed Execution & Safe Defaults:**
  - Secure permission checks on disk/network operations.
  - Cross-platform byte-order and architecture abstractions.

