# Proposal 000001
### Name
##### Explicit function return types
### Reasoning
By requiring the user to write the return type of a function, it ensures better readability of any function written. No longer would the function name has to state the return type, or have the programmer read the function to understand it.
### Syntax
The return type would come between the `def` keyword and the name of the function.

Python:
```
def func() -> None:
    pass
```
PyPlus:
```
def void func() {}
```