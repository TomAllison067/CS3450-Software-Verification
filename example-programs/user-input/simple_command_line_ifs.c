
// This program takes a command line arg and if the condition passes it will throw a buffer overflow.
// You can't pass command line args to CBMC but will create some for you.
// In this case CBMC will create 2 possible values for nr based on the if condition and will throw an buffer overflow error.

// cbmc .\simple_command_line_ifs.c --bounds-check --trace

int main(int argc, char* argv[]) {
	int nr = argv[0];

	if (nr < 0) {
		int buffer[10];
		buffer[20] = 10;
	}
}