# Proposal 000006
### Name
##### Addition of logical operators
### Reasoning
Most other languages will require the use of symbols for logical operators `||` and `&&` whereas Python has keywords for these. It would be benificial to implement these symbol based operators, and it would take no extra work to keep support of both words and symbols allowing the programming to pick and choose their preference.
### Syntax
Python:
```
if (True or False) and (i == 0)
```
PyPlus:
```
if (true || false) && (i == 0)
#or
if (true or false) and (i == 0)
#both can easily be supported
```