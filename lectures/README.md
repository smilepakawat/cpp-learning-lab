# Modern cpp for programmers

## Contents

- The Basic
- User-Defined Types
- Modularity
- Error Handling
- Classes
- Resource Management

## The Basic

cpp is compiled language
the iso c++ standard
    - core
    - standard lib
c++ is statically typed language

hello world program

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
}
```

function declaration

- Tells the compiler that a function exists, its return type, and the types of its parameters, without providing the body.
- Also known as a **function prototype**.

```cpp
double sqrt(double);          // declaration only
int add(int a, int b);       // parameter names are optional in declarations
```

function define

- Provides the actual body (implementation) of a function.
- A definition also serves as a declaration.

```cpp
double sqrt(double d) {
    // ... implementation ...
}

int add(int a, int b) {
    return a + b;
}
```

semantics of argument passing

- **Pass by value**: a copy of the argument is made; changes inside the function do not affect the caller.
- **Pass by reference (`&`)**: the function operates on the original object; can modify the caller's data.
- **Pass by const reference (`const &`)**: avoids copying while preventing modification — preferred for large objects.
- **Pass by pointer (`*`)**: passes the address; the function can modify the original or accept `nullptr`.

```cpp
void by_value(int x)           { x = 0; }          // caller's value unchanged
void by_ref(int& x)            { x = 0; }          // caller's value changed
void by_const_ref(const int& x){ /* read only */ }  // no copy, no modify
void by_ptr(int* p)            { if (p) *p = 0; }  // caller's value changed via pointer
```

function overloading

- Multiple functions can share the same name if they differ in the **number** or **types** of their parameters.
- The compiler resolves the call at compile time (overload resolution).
- If the compiler cannot determine a unique best match, it reports an **ambiguity error**.

```cpp
void print(int);
void print(double);
void print(string);

void print(int, double);
void print(double, int);

void user() {
    print(0, 0); // error: ambiguous — could be print(int,double) or print(double,int)
}
```

auto

- Lets the compiler **deduce** the type of a variable from its initializer.
- Useful when the type is obvious or verbose (e.g., iterator types).
- Does **not** mean the variable is untyped — the type is fixed at compile time.

```cpp
auto x = 42;          // int
auto d = 3.14;        // double
auto s = "hello"s;    // std::string (with the s literal suffix)

std::vector<int> v{1, 2, 3};
auto it = v.begin();  // std::vector<int>::iterator
```

scope and lifetime

- **local scope**: declared inside `{}` — exists from declaration to end of block.
- **class scope**: members of a class — accessible through the object or within member functions.
- **namespace scope**: declared inside a namespace — accessible by prefix or `using` declaration.
- **global scope**: declared outside any block/namespace — exists for the entire program duration.
- An object created by `new` "lives" until destroyed by `delete`.

constant

```cpp
constexpr int dmv = 17;
int var = 17;
const double sqb = sqrt(var);

double sum(const vector<double>&);
vector<double> v{1.2, 1.3, 1.4};
const double s1 = sum(v);
constexpr double s2 = sim(v);
```

const vs constexpr

- `const`: promises the variable will not be changed after initialization; the value may be computed at **run time**.
- `constexpr`: the value must be computable at **compile time**; enables compile-time evaluation.

```cpp
const int x = runtime_func();     // OK — value decided at run time
constexpr int y = 42;             // OK — value known at compile time
constexpr int z = runtime_func(); // ERROR — cannot evaluate at compile time
```

c++ pure functions
    - cannot have side effect
    - cannot modify non-local variables
    - can only use information passed to them as arguments
    - can have loop and use their own local variables
example

```cpp
constexpr int square(int x) {
    return x * x;
}
```

if and switch with init (C++17)

```cpp
if (auto it = m.find(key); it != m.end()) {
    // it is visible here
}

switch (Status s = get_status(); s) {
    case Status::ready:
        // ...
        break;
}
```

pointer, arrays and references

- **Pointer (`*`)**: holds a memory address; can be reassigned or set to `nullptr`.
- **Array**: a fixed-size contiguous block of elements; decays to a pointer when passed to a function.
- **Reference (`&`)**: an alias for an existing object; must be initialized at declaration and cannot be reseated.

```cpp
int x = 10;
int* p = &x;   // pointer to x
int& r = x;    // reference to x — r and x are the same object
int a[5];      // array of 5 ints
```

++i vs i++ in term loop

- `++i` (pre-increment): increments first, then returns the new value.
- `i++` (post-increment): returns the current value, then increments.
- In loops with primitive types (`int`), **no performance difference**.
- For iterators and complex types, **`++i` is preferred** because `i++` may create a temporary copy.

```cpp
for (int i = 0; i < n; ++i) { /* preferred style */ }
```

the null pointer

- `nullptr` (C++11) is a type-safe null pointer constant (type `std::nullptr_t`).
- Prefer `nullptr` over `NULL` or `0` to avoid ambiguity with integer overloads.

```cpp
int* p = nullptr;
if (p != nullptr) { /* ... */ }
```

assignment state

- **pointer**: assignment changes which object the pointer points to.
- **reference**: assignment changes the value of the referenced object (the reference itself cannot be reseated).

```cpp
int a = 1, b = 2;
int* p = &a;
p = &b;          // p now points to b

int& r = a;
r = b;           // a is now 2 — r still refers to a
```

initialization vs assignment

- **Initialization**: gives a variable its first value at the point of declaration.
- **Assignment**: replaces the current value of an already-initialized variable.
- In C++ these are fundamentally different operations — constructors are called for initialization, `operator=` for assignment.

```cpp
int x = 42;      // initialization (copy-initialization)
int y{42};        // initialization (direct-list-initialization, C++11)
x = 100;          // assignment
```

## User-Defined Types

1.structures

```cpp
struct Vector {
    double* elem;
    int sz;
};
```

access modifier

- `public`: accessible from anywhere.
- `private`: accessible only from within the class itself.
- `protected`: accessible from the class and its derived classes.
- In a `struct`, members are `public` by default; in a `class`, they are `private` by default.

2.classes

```cpp
class Vector {
    public: 
        vector(int s) : elem{new double[s]}, s{s} {}
    private:
        double* elem;
        int s;
}
```

structure vs class

- The **only** technical difference: `struct` members default to `public`, `class` members default to `private`.
- By convention, `struct` is used for plain data aggregates (POD), `class` for types with invariants and member functions.

3.enumerations

- **enum class** (scoped enum, C++11): enumerators are scoped and do **not** implicitly convert to `int`.
- Requires explicit conversion to its underlying type via `static_cast`.
- **plain enum** (unscoped enum): enumerators leak into the enclosing scope and implicitly convert to `int`.

enum class vs plain enum

- `enum class` is **strongly typed** and scoped — prevents name collisions and accidental arithmetic.
- `plain enum` is weakly typed — convenient but error-prone.
- Prefer `enum class` in modern C++.

```cpp
enum class Color { red, green, blue };
Color c = Color::red;
int n = static_cast<int>(c);  // explicit conversion needed

enum OldColor { red, green, blue };  // names leak into enclosing scope
int x = red;                          // implicit conversion to int
```

4.uninions

```cpp
union Value {
    int i;
    double d;
};
```

std::variant (C++17)

- A type-safe union.

```cpp
#include <variant>
std::variant<int, double> v = 42;
v = 3.14;
int i = std::get<double>(v); // access
```

std::optional (C++17)

- Represents a value that may or may not be present.

```cpp
#include <optional>
std::optional<string> find_user(int id) {
    if (exists(id)) return "User Name";
    return std::nullopt;
}
```

std::any (C++17)

- Can hold a value of any type.

```cpp
#include <any>
std::any a = 1;
a = "hello"s;
```

## Modularity

separate compilation

- C++ supports splitting code across multiple files and compiling them independently.
- **Header files (`.h` / `.hpp`)**: contain declarations (function prototypes, class definitions) shared between translation units.
- **Source files (`.cpp`)**: contain definitions (implementations).
- `#include` merges headers into a source file before compilation.

```cpp
// vector.h — declaration
class Vector {
public:
    Vector(int s);
    double& operator[](int i);
    int size();
private:
    double* elem;
    int sz;
};

// vector.cpp — definition
#include "vector.h"
Vector::Vector(int s) : elem{new double[s]}, sz{s} {}
```

namespace

- A mechanism for grouping related declarations to **avoid name collisions**.
- Can be nested; C++17 allows compact nested syntax (`A::B::C`).

```cpp
namespace MyLib {
    void f();
}

// Nested namespaces (C++17)
namespace MyLib::Internal {
    void g();
}
```

function arguments and return values

- **argument passing**: by value (copy), by reference, by const reference, or by pointer (see "semantics of argument passing" above).

- **return values**:
    - value return
    - copy elision: optimization that avoids unnecessary copies.
    - return type deduction: using auto to deduce the return type.
    - structure binding: decompose an object into multiple variables (C++17).

Example: Structured binding (C++17)

```cpp
struct Point { int x, y; };
Point p{10, 20};
auto [x, y] = p; // x = 10, y = 20

std::map<string, int> m;
for (const auto& [name, age] : m) {
    // ...
}
```

Example: Return type deduction

```cpp
auto add(int a, int b) {
    return a + b;
}
```

## Error Handling

exceptions

- A mechanism for reporting and handling run-time errors.
- Use `throw` to signal an error and `try/catch` to handle it.
- Exceptions separate error-detection code from error-handling code.

```cpp
double& Vector::operator[](int i) {
    if (i < 0 || size() <= i)
        throw std::out_of_range{"Vector::operator[]"};
    return elem[i];
}

try {
    v[v.size()] = 7;  // will throw
} catch (std::out_of_range& e) {
    std::cerr << e.what() << '\n';
}
```

invariants

- A condition that must always hold true for a class to be in a valid state.
- The constructor is responsible for **establishing** the invariant; member functions must **preserve** it.
- Example: a `Vector` invariant might be "elem points to an array of sz doubles".

error-handling alternatives

- **returning a value indicating failure**: e.g., returning `std::optional`, an error code, or a sentinel value like `-1` or `nullptr`.
- **throwing an exception**: best when the error cannot be handled locally and must propagate up the call stack.
- **terminate the program**: use `std::terminate()` or `exit()` for unrecoverable errors; also the default when an exception is not caught.

## Classes

concrete types
    - arthimetic type
    - a container
    - constructor/destructor combination
abstract types
    - Interfaces with pure virtual functions.

```cpp

class Container {
public:
    virtual double& operator[](int) = 0;
    virtual int size() const = 0;
    virtual ~Container() {}
};
```

- vector container (implements Container)
- list container (implements Container)

virtual functions
- Dynamically bound functions.

```cpp
class Shape {
public:
    virtual void draw() = 0; // Pure virtual
    virtual ~Shape() {}
};
```

class hierarchies

```cpp
class Circle : public Shape {
public:
    void draw() override { /* ... */ }
};
```

avoiding resource leaks
- Use smart pointers (RAII).
```cpp
std::unique_ptr<Shape> s = std::make_unique<Circle>();
s->draw(); // Automatically destroyed when s goes out of scope.
```

## Resource Management

- RAII (Resource Acquisition Is Initialization).
- default implementations: using =default and =delete.
- conversion: explicit vs implicit.
- member initializer: initialize members directly in the constructor.
- copy and move: ensure correct resource handling.

Example: Member initializer

```cpp
class Vector {
    double* elem;
    int sz;
public:
    Vector(int s) : elem{new double[s]}, sz{s} {} // Initializer list
};
```

Example: Move semantics (C++11) and Structured bindings (C++17)

```cpp
std::vector<string> v;
v.push_back(std::move(s)); // Transfers ownership
```

std::string_view (C++17)

- Non-owning view of a string.

```cpp
#include <string_view>
void log(std::string_view msg) {
    std::cout << msg << std::endl;
}
```

std::filesystem (C++17)

- File system manipulation.

```cpp
#include <filesystem>
namespace fs = std::filesystem;
fs::path p = "data/order_book.csv";
if (fs::exists(p)) { /* ... */ }
```
