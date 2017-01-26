# funcRedirect [![Build Status](https://travis-ci.org/mensinda/funcRedirect.svg?branch=master)](https://travis-ci.org/mensinda/funcRedirect) [![Coverage Status](https://coveralls.io/repos/github/mensinda/funcRedirect/badge.svg)](https://coveralls.io/github/mensinda/funcRedirect)

Redirects function calls at runtime.

Most of the code is based on https://github.com/gzc9047/CppFreeMock

## :warning: WARNING :warning:

This library dynamically rewrites functions at runtime!
It is also not thread save!

USE WITH CAUTION!!!

## Supported Platforms

### Processor architectures

 - X86

### Operating systems

 - POSIX compatible OS (all \*nix)

## Example

```cpp
class AAA {
 public:
  std::string func1() { return "FUNC1"; }
};

class BBB : public AAA {
 public:
  std::string func2() { return "FUNC2"; }
};

int func3(int i) { return i; }
int func4(int i) { return (-1) * i; }

int main() {
  AAA a;
  BBB b;

  {
    a.func1()  // returns "FUNC1"
    func3(100) // returns 100

    Redirector r;
    r.redirect(&AAA::func1, &BBB::func2);
    r.redirect(&func3, &func4);

    a.func1()  // returns "FUNC2" (BBB::func2 is executed)
    func3(100) // returns -100    (func3 is executed)
  }

  // Destroying r restores the original functions
  a.func1()  // returns "FUNC1"
  func3(100) // returns 100

  return 0;
}
```
