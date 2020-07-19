# Stack Assembly Interpreter

This project provides the C++ implementation of a simple Assembly language of a fictional machine which only have one stack and no register.

# The Machine
## Description

This is an informal design for a stack interpreter that manipulates **32-bit** signed integers and understands a few instructions.

In the following **TOP** denotes the element on top of the stack, and **SECOND** the second element on top of the stack.

Each instruction has an index in the code, starting from 0, and an optional integer argument, as in ``3 POP 2`` which is the forth instruction of the listing, named ``POP`` with a single argument 2.

## Assembly instructions

### READ
	Reads an integer on stdin and push the value on the stack, or exit if input is invalid.

### WRITE
    Pops the top value of the stack, and prints it on stdout.

### DUP
    Duplicates the value on top of the stack.

### MUL
    Pops the two top value of the stack, multiply them and push the result on top of the stack.

### ADD
    Pops the two top value of the stack, add them and push the result on top of the stack

### SUB
    Pops the two top value of the stack, sub the TOP with the SECOND and push the result on the stack.

### DIV
    Pops the two top value of the stack, computes the integer division between
    TOP and SECOND and push the result on the stack.

### MOD
    Pops the two top value of the stack, computes the modulo between
    TOP and SECOND and push the result on the stack.

### GT/LT/EQ
    Pops the two top values from the stack, compare them for TOP > SECOND,TOP < SECOND
    or TOP == SECOND and push the result as 0 if the comparison is met,
    as 1 otherwise and push the result on the stack.

### JMPZ < n >
    Pops the two top value of the stack. Jump to the <n>th instruction,
    where <n> was the first value on the stack, if the second value is null.
    Otherwise just drop these two values.

### PUSH < n >:
    Push the integer value <n> on the stack.

### POP <n>
    Pop <n> value(s) from the stack.

### ROT < n >
    Perform a circular rotation on the first n value of the stack toward the top
    for instance the stack : BOTTOM [1,2,4,8] TOP becomes BOTTOM [1, 8, 2, 4] TOP after ROT 3.

## Example
The following program reads a number and prints its value squared if the value is positive or null, and 0 otherwise.

	0 READ
	1 DUP
	2 PUSH 0
	3 GT
	4 PUSH 8
	5 JMPZ
	6 POP 1
	7 PUSH 0
	8 DUP
	9 MUL
	10 WRITE
	
# Compilation and installation
This project requires a recent compiler supporting **C++17** to work. It is not plaftorm dependent thus it can be compiled on Windows, Linux, OS X or other systems. A Makefile is already provided for compilation with **GCC** (**MinGW** on Windows or **Clang** on OS X can also work as GCC is aliased to Clang).

The generated binary is an interpreter that will need a **.sa** file containing all assembly instructions as described above. A file example is available in the next section.



### Compilation

Go in the root folder of the project and simple run:

	make

### Clean

Go in the root folder of the project and simple run:

	make clean

### Run
Go in the bin folder and run for instance:

	./sai ../samples/factorial.sa

# .sa file format

**.sa** files are read and executed by the Stack Assembly Interpreter. For each instruction, the instruction offset (integer), instruction name and eventual optional argument must be precised. Comments are also supported on the right of each instruction. Each instruction offset **MUST** be subsequent:

	0 PUSH 5
	1 PUSH 2
	2 MUL
	3 WRITE

Will work. However:

	0 PUSH 5
	1 PUSH 2
	5 MUL
	10 WRITE

**WON'T** work.

## File example

Here is a file example:

	0 READ // Read input from user
	1 PUSH 2
	2 ROT 2 // Swap the two values for comparison
	
	3 MOD
	4 PUSH 0
	5 EQ
	
	6 WRITE // Will display '0' if the entered number in even, '1' if it is odd

## Samples
A list of samples is also available in the "**samples**" folder of the project:

 - **square**: Reads a positive value from stdin and display its square value as a result.
 - **factorial**: Reads a value from stdin and display the factorial value.
 - **oddeven**: Takes a number as input and display '0' if the number is even, '1' otherwise.

