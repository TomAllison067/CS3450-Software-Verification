
// This program takes a command line arg and if the condition passes it will throw a buffer overflow.
// You can't pass command line args to CBMC but will create some for you.
// In this case CBMC will create 2 possible values for nr based on the if condition and will throw an buffer overflow error.

int main(int argc, char* argv[]) {
	int nr = argv[0];

	if (nr < 0) {
		int buffer[10];
		buffer[20] = 10;
	}

	nr = (nr * 10 - nr + 1000) / 3;

	if (nr > 20) {
		if (nr < 100) {
			if (nr > 98) {
				int buffer[10];
				buffer[20] = 10;
			}
		}
	}
}