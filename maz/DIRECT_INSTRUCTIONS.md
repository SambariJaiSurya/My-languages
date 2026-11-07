<p align="center">
  <img src="assets/logo.svg" alt="maz logo" width="100"/>
</p>

# MAZ — Quick Start & Installation Guide

> **Direct, zero-theory instructions for anyone downloading and using the MAZ language.**

---

## 1. Clone the Repository

```bash
git clone https://github.com/SambariJaiSurya/My-languages.git
cd My-languages/maz
```

---

## ⚡ 1-Click Automated Setup (Windows)

Just double-click **`RUN_ME.bat`** (or in PowerShell run `.\setup.ps1`).

It automatically:
1. Builds the compiler (`maz.exe`).
2. Adds `maz` to your system PATH (so you can run `maz` anywhere).
3. Installs the VS Code and Antigravity extensions.
4. Activates the custom MAZ logo file icons for all `.maz` files.

---

## Manual Setup (If you prefer running commands manually)

### 1. Build MAZ

Compile the executable with zero external dependencies (requires any C++20 compiler: GCC, Clang, or MSVC):

### Windows (PowerShell or CMD):
```powershell
.\build.ps1
```
*(or run `build.bat`)*

### Linux / macOS:
```bash
g++ -std=c++20 -O2 -I src src/lexer/Lexer.cpp src/parser/Parser.cpp src/runtime/Environment.cpp src/runtime/Interpreter.cpp src/main.cpp -o maz
```

---

## 3. Use `maz` from Any Folder (Add to PATH)

Run this command once from inside the `maz` folder to use `maz` everywhere on your computer:

### Windows (PowerShell):
```powershell
[Environment]::SetEnvironmentVariable("Path", [Environment]::GetEnvironmentVariable("Path", "User") + ";$((Get-Location).Path)", "User")
```
*(Restart your terminal after running this).*

### Linux / macOS:
```bash
echo "export PATH=\"\$PATH:$(pwd)\"" >> ~/.bashrc && source ~/.bashrc
```

---

## 4. Enable VS Code Syntax Highlighting

Run this command once to install the syntax highlighting extension into your VS Code:

### Windows:
```powershell
Copy-Item -Recurse "tools\vscode-extension" "$env:USERPROFILE\.vscode\extensions\maz-language-support"
```

### Linux / macOS:
```bash
cp -r tools/vscode-extension ~/.vscode/extensions/maz-language-support
```
*(Restart VS Code).*

---

## 5. Write Your First Program

Create a file named `hello.maz`:

```maz
display("Hello from MAZ!")

name = "Developer"
display("Welcome, " + name + "!")

for (new i = 1, i <= 3, i++) {
    display("Count: " + i)
}
```

---

## 6. Run Your Program

### From any terminal:
```bash
maz run hello.maz
```
*(or simply `maz hello.maz`)*

### From inside VS Code:
Open `hello.maz` and press:
```
Ctrl + Shift + B
```

### Start the Interactive REPL:
```bash
maz repl
```

---

## 7. Run the Test Suite

Verify that everything works properly on your machine:

```powershell
powershell -ExecutionPolicy Bypass -File tests/run_tests.ps1
```

---

## 8. Syntax Quick Reference (Copy & Paste)

```maz
// Variables & Automatic Type Inference
count = 10
price = 19.99
isReady = true
const MAX = 100

// Dynamic Variables ('dyn') and Forced Types ('force')
dyn dynamicVal = 50
dynamicVal = "now a string" // Allowed because it's dyn

x = 100
force x = "re-typed string" // Allowed via force

// Loops: Three-Part Loop with Commas & 'new' Scoping
for (new i = 0, i < 5, i++) {
    display("Index: " + i)
}

// Conditions (C++ Style)
if (count >= 10) {
    display("High")
} else if (count >= 5) {
    display("Medium")
} else {
    display("Low")
}

// Functions with Default Parameters
def greet(user = "Guest", prefix = "Hello") {
    return prefix + ", " + user + "!"
}

display(greet())
display(greet("Alice", "Welcome"))
```
