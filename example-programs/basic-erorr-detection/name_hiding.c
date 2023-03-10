void foo(void)
{
	int i = 15;
	int MyArray[10];

	for (int i = 0; i < 10; ++i)
	{
		MyArray[i] = 0;
	}

	// whatever was intended . .
	MyArray[i - 1] = 1;
	// .. out-of-bounds results
}