
## What is CBMC?
CBMC is a sound bounded model checker for C programs. 

The user can provide properties to be checked, relating to, for example, memory leaks, pointer safety, and division by zero (http://www.cprover.org/cprover-manual/properties/).

It can be used on all sorts of software, but one particular domain mentioned is software with real-time guarantees. For example, embedded software in hardware controllers may have 
strict bounds on the number of iterations in loops, in which case CBMC is able to verify these bounds using loop unwinding, which will be elaborated on later in this video.

CBMC is a sound tool, rather than a complete tool. It proves the absence of errors by verifying that properties hold on programs, rather than trying to find bugs. Note that its soundness
 is in context of the right properties being verified: the user can provide many properties to the command-line, e.g. `--memory-leak-check` and `--bounds-check`, but if you don't provide
 the right properties for your program, then certain bugs may not be found.

## How it does it
A property is defined as the state of the program when the program reaches a program location. 

Properties are specified using assertions. If you weren't to use CBMC, you could write assertions in the code directly using the `assert` macro from the `assert.h` C libary, and any 
assertions that fail would only be caught at run-time. CBMC has an assertion generator that automatically generates assertions under the hood according to the properties specified,
and checks these along with any programmer-written assertions without needing to compile the program.

Using a technique called symbolic simulation, CBMC translates the program into a boolean formula, which is then passed to a built-in SAT solver which verifies each property holds.
(ref: http://www.cprover.org/cprover-manual/introduction/ http://www.cprover.org/cprover-manual/cbmc/tutorial/) 

These properties are all reachability properties. That is, CBMC asks the question "Is there a path through the program
such that some property is violated?"

If a property is violated, then CBMC can generate a counterexample in the form of a program trace.

## Race conditions and segmentation faults
This program is a beefed up version of one available from the CBMC tutorial, which comes with a race condition, and we've added a pointer error too.

In this program, we have variable g that is shared by two threads. We launch a thread that sets the value of g to 2, and then set it to 1 in the main thread.

The user-programmed assertion here asserts that g should be equal to 1, but depending on the order of execution of the threads, this assertion may fail.

The thread ID returned by `pthread_create` is stored in a struct, and we've declared a pointer to this struct without actually allocating any memory for it.
If we run this, we'll hit a segmentation fault.

Running this with the `--pointer-check` option reveals that the program fails various properties related to pointer dereferencing, seen in figure 3.

In figure 2, we show the tail-end of a program trace which shows `g` being set to 1 in thread 0, and then 2 in thread 1, before the assertion fails.

Note that even with correct pointer handling, we could run this many times over (as we did) and never hit the assertion failure at runtime - but imagine if this was some
safety critical software, we wouldn't want even the slightest chance of failure!

## Loop unwinding 1
http://www.cprover.org/cprover-manual/cbmc/unwinding/

CBMC models a program's execution up to a bounded number of steps, achieved by a process known as loop unwinding. This can be thought of as the checker transforming loop code into equivalent
code without loops. For example, figure 1 on the right shows a while loop. If we tell the model checker to search for bugs for up to five iterations, then it corresponds to checking the loop-free code
in figure 2, which has 5 nested if statements.

CBMC can often automatically determine an upper bound on the number of loop iterations. 

Figure 3 shows code with an upper bound of 100, but note that the loop could prematurely terminate depending on the return value
of some function f(), for which we do not know the implementation. 

Even though the bound is not constant, CBMC may still be able to unwind the loop to completion - and in this case, it can.


## Loop unwinding 2
The automatic detection of loop unwinding bounds may fail if the number of loop iterations is highly data-dependent, or, in this example, depends on user input.

In the program in figure 1, there is an array-out-of-bounds error that occurs on line 17 if the value of i is greater than or equal to 10. If we compile and run this program, it'll ask us 
for input to set the value of `n`. If `n` is greater than 10 then `i` is set to a value >= 10 and the inner if statement is entered, 
and we assign to an array outside of its bounds.

Again, this program will compile and run without any errors - but this is dangerous: buffer overflow attacks can happen if someone assigns malicious code to a certain address next to an array,
which can be executed if we access that address by accident in our program. We really need to be able to avoid manipulating addresses which we shouldn't be able to.

If we run CBMC on this using the bounds check option without specifying an unwinding limit, it'll unwind the loop indefinitely and the analysis will never finish.

To fix this, we can set the unwind limit for all loops in the program with the `--unwind` option, or for specific loops in the program with the `--unwindset` option.

## Properties are important!
CBMC is sound in the sense that for all properties it seeks to verify, if there are no failures, then it really is the case that no properties have failed to verify - but,
 we still need to pass cbmc the correct options.

In the program on the right, we declare a pointer to an int with memory allocated for 10 integers, and we treat this as an array. We assign 10 values to this array,
but print 11 values later in the program. This is valid C: we're really just doing pointer arithmetic. 

If we run this program, the last value printed out is some random number, because we're accessing some random memory just after the array.
We mentioned buffer overflow attacks earlier on: if someone had put malicious code into the memory where we access the 11th index, we'd be in trouble.

Now, with this program, we thought we'd finally found a bug that CBMC claims to find but actually doesn't - we ran it with the `--bounds-check` property and the verification passed.

It turns out we were wrong: we needed to run it with the `--pointer-check` property, because it's a pointer, not an array,
and so the verification fails: we get a dereference failure, "pointer outside object bounds".

So, CBMC really is very good - we didn't manage to beat it, but it does reinforce the point that it's important to specify the right properties to be checked.

## Large programs
CBMC also works for non-trivial programs of course - we downloaded a tic-tac-toe program (https://github.com/mishal23/Tic-Tac-Toe) from github and ran CBMC on it. Now, interestingly, we got different
results - on one Windows machine, with these flags we had 4 failures out of 592 checks, but on Unix we had 8 failures out of 399 checks and had to use the `--object-bits 63` option which sets the
number of bits used for object addresses, or cbmc would fail.

Note, for verifying modules or components of larger programs without a `main` function, you can use the `--function` option to tell CBMC which function to use as its entry point.

## Useability and problems
Another issue is that CBMC claims to verify C++, but we couldn't get it to work at all. You can specify different language standards for C and C++, e.g. using the `--cpp11` option
for C++ 11 (where it defaults to C++ 98), but with both language standards we got different errors.

So, overall, CBMC is a really great program - but it seems like you have to know what you're doing with it: if you were using it as part of a large team and people were using different systems, you may 
well get different results. We also tried to run it on student final year games projects that used graphics libraries, but CBMC wouldn't work on any program with a graphics library that we tried.

Note, some of these games were written in C++.

Still, it's great for catching dangerous runtime errors, and can clearly be incredibly helpful in the right environment.