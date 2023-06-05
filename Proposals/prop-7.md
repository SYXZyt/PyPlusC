# Proposal 000007
### Name
##### Static keyword to replace staticmethod
### Reasoning
Instead of having to use `@staticmethod` to mark a method as static, a specific keyword can now be added before the `def` keyword to make it clear which methods are static and which are not. Keeps the syntax more inline with C/C++ and other OOP languages. Additionally, `@staticmethod` can be kept for any programmer who prefers that syntax.
### Syntax
Python:
```
class MyClass:
    @staticmethod
    def StaticMethod():
        pass

    def NonstaticMethod(this):
        pass

x = MyClass()
MyClass.StaticMethod()
x.NonstaticMethod()
```
PyPlus:
```
class MyClass
{
    static def StaticMethod(){}
    def NonstaticMethod(this){}
}

x = MyClass()
MyClass.StaticMethod()
x.NonstaticMethod()
```