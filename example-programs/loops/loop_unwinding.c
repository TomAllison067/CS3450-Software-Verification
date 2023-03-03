
// This program will throw a buffer overflow error after the 10th iteration.
// If you don't properly specify to cbmc the number of loop umwinds it has to do, it might not find the bug.
// 
// Will not find the bug: cbmc .\loops_unwinding.c --bounds-check --unwindset main.0:10 
// Will find the bug: cbmc .\loops_unwinding.c --bounds-check --unwindset main.0:11
//
// main.0 means the first loop in the program and after that are unwinds range (0-10) or (0-11)

int main() {
    for (int i = 0; i < 100; i++) {
        if (i >= 10) {
            int buffer[10];
            buffer[20] = 10;
        }
    }
}