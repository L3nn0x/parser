Parser
======

A flex/bison version of master.
In order to compile this branch, you will need flex, bison, gcc, and make.

Just type :

```
make
```

Then you can try the calculator :

```
./bin/a.out
```

The following expressions and instructions can be evaluated :

- Basic arithmetic : `-2 + 44.6;`
- Variables assignement : `x <- 42`
- Variable destruction : `x <- x` (x will be undefined after this instruction)
- Variable evaluation : `x <- 21 * 2; x;` (-> 42)
