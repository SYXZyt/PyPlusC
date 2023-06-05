# Proposal 000005
### Name
##### Constructor shares class name
### Reasoning
Keeps clear which function is the classes constructor since they share the same name. Keeps the class cleaner.
### Syntax
Python:
```
class MyClass:
    def __init__(this):
        pass
```
PyPlus:
```
class MyClass
{
    def MyClass(this) {}
}
```