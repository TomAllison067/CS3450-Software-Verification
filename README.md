# Software Verification

Structure (not set in stone):
* `notes/` for our collective ramblings .etc about CBMC
* `example-programs/` - write `*.c` programs in here, and run `./compile.sh` to compile anything in that directory to the `build/` directory, and `./clean.sh` to clean it.
  * `build/` is in the `.gitignore` file to prevent people spamming the repo with random programs all over the plae
  * cbmc does static analysis without needing compiled files - so actually, probably don't need the build folder + makefile

## Examples
`cbmc example-programs/simpleBufferOverflow.c --show-properties --bounds-check`
