# Semicolon

Semicolon is an esoteric programming language that revolves around a single character: ';'. It's an interpreted programming language that stimulates a stack, memory tape, and set of instructions. This effectively makes the language turing complete.

## Files
### main.c
This is the main file that copies the semicolon file to a buffer, tokenizes it, and then interprets the tokens
### tokenizer.c
This tokenizes the raw input into numbers. Each number corresponds to an op code for the interpreter. Each number is a direct translation of the number of consecutive semicolons it encounters;
### interpreter.c
This runs the op codes.
### obfuscate.py
Since the tokenizer doesn't care about any characters that are not semicolons, obfuscation is simple to do as we can just insert random characters between teh consecutive runs of semicolons. As long as the number of semicolons in each consecutive run of semicolons stays the same, the program will behave the same way.
### fib.;
Semicolon files have a semicolon ';' as their file extension. This is a relatively simple semicolon program that prints out some fibonacci numbers
### fib\_obfuscated.;
This is the obfuscated version of fib.;.

## Op Codes

1: MOVE_LEFT - move tape read head to the left

2: MOVE_RIGHT - move tape read head to the right

3: READ - read from memory to stack

4: WRITE - write from stack to memory

5: LOAD_ONE - load 1 to stack

6: DOUBLE\_STACK\_TOP - double top element of stack

7: JMP - load function from stack, jump to location

8: CMP - pop cmp value, pop 3 more, push compared value back

9: READ\_STDIN\_NUM - read a number from stdin to stack

10: WRITE\_STDOUT\_NUM - write a number from stack to stdout

11: ADD - second pop + first pop, push result

12: SUB - second pop - first pop, push result

13: MUL - second pop * first pop, push result

14: DIV - second pop / first pop, push remainder, then quotient

15: READ\_STDIN - read a char from stdin to stack

16: WRITE\_STDOUT - write a char from stack to stdout
