# PyPlus
Python is a great and powerful programming language, but there are a few slight annoyances which cause me to dislike the language.
Introducing PyPlus, a Python wrapper language which removes all of these annoyances.
***
## Why use PyPlus?
PyPlus is a custom syntax which compiles directly into Python. This means it can work with any existing Python library, and can even call `.py` files. If you can code it in Python, you can code it in PyPlus.

This project was created because I dislike using Pythons whitespace based scoping and wanted to replace it with curly braces instead, while retaining everything that makes Python great.

## Can Python call PyPlus code?
No. Python cannot call PyPlus code as PyPlus is not valid syntax for the Python compiler. First, you would have to compile the PyPlus code first, before compiling it with Python.
PyPlus can call Python as the PyPlus compiler does not evaluate imports. Just be aware that the PyPlus compiler cannot compile Python, and will generate incorrect code if ran.

## Can I compile PyPlus to an executable
No. The compiler originally could, however there are issues when PyInstaller is ran from a Python script, and so the feature had to be removed. If you want to compile to `.exe`, you will have to run PyInstaller on the generated Python files.

## How I can make a curly bracket appear in the compiled Python?
Since the PyPlus compiler will convert all curly brackets into indents, you can use some keywords to act as a pass through.
```
#Python
myMap = {}
myMap2 = {
    "a" : "b"
}
```
```
#PyPlus
myMap = PyPlus_EmptyMap
myMap2 = PyPlus_OpenCurly
    "a" : "b"
PyPlus_CloseCurly
```
The readability isn't great but it is the only I could think of doing it
In a future build, backslashes will be used

In the next update, a backslash will be used instead.
```
myMap = \{\}
#or
myMap2 = \{
    "a" : "b"
\}
```

## PyPlus vs Python
Currently the main differences is that PyPlus uses curly braces for classes and functions, in the same way `C/C++` or `Java` do for example.
The list of new features is always expanding. Check out [plans.md](https://github.com/SYXZyt/PyPlus/blob/master/Plans.md) for a list of changes which will be made.

## Changes
Removal of whitespace
```
#Python
def main():
    print("Hello")
```
```
#PyPlus
def main()
{
    print("Hello")
}
```

Renaming of booleans
```
#Python
flse = False
tre = True
```
```
#PyPlus
flse = false
tre = true
```

Renaming of None
```
#Python
myVar = None
```
```
#PyPlus
myVar = null
```
## Known Issues
Multiline strings are likely to give you an error, as the PyPlus compiler sees them as a group of strings next to each other. This is on the list of things to fix.
Attempting to compile a Python file will result in a mangled `.py` which contains incorrect indentation.
Cannot use maps as the brackets will compile into indents. (This is semi-fixed. Keywords can be used to bypass this issue)
