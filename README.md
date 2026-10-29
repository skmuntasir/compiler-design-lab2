# Compiler Design Lab 2: Symbol Table and Parser

**Author:** Sk Tasrian Muntasir
**ID:** 21101345
**Course:** Compiler Design Lab, BRAC University

A Flex/Bison parser for a small C-like language that builds a symbol table with nested scope tables. It reports multiple-declaration errors and logs every grammar rule it reduces.

## Files

| File | Purpose |
|------|---------|
| `21101345.l` | Flex scanner (tokens) |
| `21101345.y` | Bison grammar, semantic actions, scope handling |
| `symbol_info.h` | Symbol entry (name, type, category, data type, array size, params) |
| `scope_table.h` | Hash-table based scope table |
| `symbol_table.h` | Stack of scope tables |
| `input1.c` | Sample input |
| `21101345_log.txt` | Sample output log for `input1.c` |
| `script.sh` | Build and run script |

## Build and run

Requires `flex`, `bison` and `g++`.

```bash
bison -y -d --verbose 21101345.y
g++ -w -c -o y.o y.tab.c
flex 21101345.l
g++ -fpermissive -w -c -o l.o lex.yy.c
g++ y.o l.o -o a.out
./a.out input1.c
```

On Windows, `script.sh` produces `a.exe` and runs `./a.exe input1.c`.

The output is written to `21101345_log.txt`.
