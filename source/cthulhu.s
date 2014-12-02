@ the gba stuff tends to use thumb rather than arm for asm
@ this means we can only use registers r0-r7 except with add, mov and cmp
@ and we have a restricted instruction set

@ parameters passed from c function calls are stored in order in r0-r3 (automatically uses the stack after 4 parameters)
@ to return a value we must make sure we pass a pointer from c and write to it via the corresponding asm register



@ refer to this: http://www.coranac.com/tonc/text/asm.htm
@ also this: http://www.heyrick.co.uk/assembler/qfinder.html

@ here's what's going to happen...
@ myfunc will take the pointer you pass from C, access the variable and add 1 to it.
@ myfunc will then call myfunc2, which will add another 9 to the variable
@ therefore, each call of myfunc from C, your number will go up by 10.

.THUMB				@ turn on thumb
.ALIGN  2			@ no idea why we do this
.GLOBL  myfunc		@ name of first function goes here
.GLOBL	myfunc2		@ name of 2nd function goes here
.GLOBL	scream


.THUMB_FUNC			@ we are about to declare a thumb function
					@ c equivalent: void myfunc(int* answer);
					@ the address passed into "answer" will be stored in r0 upon calling the function
					
myfunc:				@ function start

push { r4-r7, lr }	@ push r4-r7 and link register onto stack. Your function might use these
					@ registers, so we need to preserve the values just in case!
					@ we don't need to worry about r0-r3 as it is assumed they will be regularly messed up anyway
					
						@ r0 will automatically contain the address of the first parameter passed from C.
	ldr r4, [r0]		@ dereference it into r4 - use square brackets when dealing with addresses!
	add r4, #1			@ add 1 to value in r4 - # indicates a "raw" number
	str r4, [r0] 		@ store data in r4 at r0 address
	
	bl myfunc2 			@ branch and link to (i.e. "call") the function myfunc2 below

pop { r4-r7 }		@ pop first 4 values from stack back into r4-r7, and also
pop { r3 }			@ pop the next value from stack (stored value for lr) into some unused register, e.g. r3 - we cannot overwrite lr so we have to do it via a normal register
bx r3				@ "branch and exchange" (return) back to C, using the previous value for lr stored in r3
@ ==================================



@ ADVANCED:
@ if doing an asm file that actually calls further asm functions, you must make sure r0-r3 do not contain anything important 
@ (apart from parameters to be passed on) as the next function will take ownership of these registers. 
@ you can always save registers on the stack before calling a function,
@ then put them back after the function has finished 
@ you also need to "branch with link" to call an asm function - this will store the current program location
@ in order to return to the correct place in the calling function once the sub-function has finished

.THUMB_FUNC			@ we are about to declare another thumb function
					@ there is no C equivalent this time - it is only called by other asm functions
					@ this function expects a memory address to already be stored in r0
					@ so we need to make sure we only call this function when we have an address in r0

myfunc2:			@ function starts here

push { r4-r7, lr }	@ preserve r4-r7 and lr as before...

	ldr r4, [r0]		@ hopefully whichever function called this left a memory address in r0 - dereference value into r4
	add r4, #9			@ add 9 to value in r4
	str r4, [r0] 		@ store data in r4 at r0 address


pop { r4-r7 }		@ pop first 4 values from stack into r4-r7, and also
pop { r3 }			@ pop the next value from stack (old value for lr) into r3 - we cannot overwrite lr so we have to do it via a normal register

bx r3 				@ "branch and exchange" (return) back to calling function, using the previous value for lr stored in r3

.THUMB_FUNC

scream: