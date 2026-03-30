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

function define

semantics of argumrnt passing

function overloading

```cpp
void print(int);
void print(double);
void print(string);

void print(int, double);
void print(double, int);

void user() {
    print(0, 0); // error
}
```

auto

scope and lifetime
    - local scope
    - class scope
    - namespace scope
    - global scope
    - An object created by new "lives" until destroyed bt delete

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

c++ pure functions
    - cannot have side effect
    - cannot modify non-local variables
    - can only use information passed to them as agruments
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

++i vs i++ in term loop

the null pointer

assignment state
    - poniter
    - reference

initialization vs assignment

## User-Defined Types
1.structures
```cpp
struct Vector {
    double* elem;
    int sz;
};
```
access modifier

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

3.enumerations
    - enum class
    - explicit conversion to lts underlying type
    - plain enum
enum class vs plain enum

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
separate compileation
    - header files

namespace
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
    - arguent passing
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
invariants
erro-handling alternatives
    - returning a value indicating failure
    - throwing an exception
    - terminate the program

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


