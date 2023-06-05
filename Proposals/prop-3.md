# Proposal 000003
### Name
##### Increment and decrement operators
### Reasoning
One of the features which Python lacks over other languages is an increment and decrement operator. In C/C++ you can easily increment a number by doing `i++` but Python requires the longer `i += 1`. Not an essential feature but a nice quality of life one.
### Syntax
Python:
```
i: int = 0
i += 1
i -= 1
```
PyPlus:
```
i: int = 0
i++
i--
```

### Additional Notes
Other languages allow these operators come inside of an expression which will increment or decrement before or after the expression (post-fix and pre-fix increment/decrement operators) which Python has no support of. This feature would be more difficult to implement as the compiler would need to figure out an expression, and add the +/-= before or after it.