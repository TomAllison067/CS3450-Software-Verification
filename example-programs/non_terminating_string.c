#include<stdio.h>
#include<string.h>

//The strings are the array or sequence of characters in the C programming language, and it is necessary to define the end
//of this sequence, this is called termination.The terminating character '\0', whose ASCII value is zero, is used for this purpose.
//Forgetting this terminating character might result in some error.
//The character array which is not terminating is a collection of characters.That's why the functions which manipulate string or
//the way C language interprets the string will cause an error. 
int main() {
	char s1[] = { 'H','e','l','l','o', '\0' };
	char s2[] = { 'H','e','l','l','o' };

	if (strcmp(s1, s2) == 0)
		printf("Same String");
	return 0;
}