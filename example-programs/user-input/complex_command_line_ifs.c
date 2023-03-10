
// This program takes a command line arg and if the condition passes it will throw a buffer overflow.
// You can't pass command line args to CBMC but will create some for you.
// CBMC will try to create a value that validates all the possible logical conditions in the program and throw a buffer overflow error and show the trace.

// cbmc .\complex_command_line_ifs.c --bounds-check --trace

int main(int argc, char* argv[]) {
	int nr = argv[0];

	if (nr < 20) {
		nr = nr * 1234 - nr / 34;

		if (nr > 100) {
			nr = nr / 99;

			if (nr < 23) {
				int buffer[10];
				buffer[20] = 10;
			}
		}
	}
}