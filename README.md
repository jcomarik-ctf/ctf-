# ctf! - Compile That File!

![CTF!](./CTF_LOGO.png)

An experimental programming language and compiler written in C.

The compiler is created specifically for the TJ (Triple J) programming language.

## The main features of the programming language TJ:
```
* precise division of code into sections.
* the ability to embed code from other low-level programming languages ​​into the main code.
* the ability to reduce the level of abstraction to a minimum.
```
## Example TJ syntax: (subject to change)

```
use{ioFlakon , strFlakon};

hide{ioFlakon};

section {data , start , end};

_data:
	
	
	num1: int;
	num2: int;
	result: int;


_start(sFlag)

	result = recf("%d+%d" , &num1 , &num2);

	
	print(result , 0);


_end(sFlag)
```
## Compiling : 
`` ctf -L2 -w .../just_test.tj -o helloworld -r  ``

## Current project state:

The project is still in development!
And will likely remain so for a very long time.
**I'm writing this on October 18, 2026, at 11:57 PM.**
