# Software Verification

Structure (not set in stone):
* `notes/` for our collective ramblings .etc about CBMC
* `example-programs/` - write `*.c` programs in here, and run `./compile.sh` to compile anything in that directory to the `build/` directory, and `./clean.sh` to clean it.
  * `build/` is in the `.gitignore` file to prevent people spamming the repo with random programs all over the plae
  * cbmc does static analysis without needing compiled files - so actually, probably don't need the build folder + makefile

## Examples
`cbmc example-programs/simpleBufferOverflow.c --show-properties --bounds-check`

# Useful links
* Manual: http://www.cprover.org/cprover-manual/
* Symbolic simulation: https://en.wikipedia.org/wiki/Symbolic_simulation
* CBMC whitepaper (A Tool for Checking ANSI-C Programs): http://www.kroening.com/papers/tacas2004.pdf
* Abstract domains / Abstract interpretation: https://en.wikipedia.org/wiki/Abstract_interpretation   
