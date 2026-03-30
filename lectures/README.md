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

```

## Modularity
separate compileation
    - header files

namespace
```cpp
```

function arguments and return values
    - arguent passing
    - value return
    - copy elision
    - return type deduction
    - structure binding

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
    - container interface
    - vector container
    - list container
virtual functions
    - create simulation virtual function table
class hierarchies
    - create example class hierarchirs
    - avoiding resource leaks
        - unique_ptr

## Resource Management
default implementations
conversion
member initializer
copy and move


