# Features to implement:
##### Format is Title, Python then PyPlus proposal
###### These are proposals and not guaranteed to be implemented
\
\
Removal of whitespace
```
def Function():
    pass
```

```
def Function() {}
```

Removal of self, and force naming to `this`

```
class MyClass:
    def __init__(self):
        self.myVar = None
```
```
class MyClass
{
    def __init__()
    {
        this.myVar = None
    }
}
```

Booleans no longer use capital letters

```
x = False
y = True
```

```
x = false
y = true
```

Change None to null

```
x = None
x = "Hello"
```

```
x = null
x = "Hello"
```

Implement void for function returns
```
def func() -> None:
	pass
```

```
def void func()
{

}
```

Change str to string

```
name : str = "PyPlus"
```

```
name : string = "PyPlus"
```

Increment and decrement

```
x : int = 0
x += 1
x -= 1
```

```
x : int = 0
x++
x--
```

Removal of elif

```
if (True)
    pass
elif (False)
    pass
else
    pass
```

```
if (true)
{

}
else if (false)
{

}
else
{

}
```

Change constructor to be same as class name

```
class MyClass:
    def __init(this)__:
        pass

```

```
class MyClass
{
    def MyClass()
    {}
}
```

Change logical operators to use symbols instead of words

```
if (True or False)
```

```
if (true || false)
```

Change comments to support end tag

```
#This is a comment, it takes a full line       print("Hello") <- This won't execute
```

```
/* This comment can end */ print("Hello") //<- This will execute
```

Implementation of `static` keyword

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

```
class MyClass
{
    static def StaticMethod(){}
    def NonstaticMethod(){}
}

x = MyClass()
MyClass.StaticMethod()
x.NonstaticMethod()
```

Implementation of macros

```
def Tau():
    return 3.1415 * 2
```

```
#define TAU 3.1415 * 2
```