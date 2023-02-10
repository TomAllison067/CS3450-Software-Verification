int func(int a)
{
	int b = a * 2;
	return b;

	// Unreachable code
	if (b < 10)
	{
		b += 10;
	}

	return b;
}
