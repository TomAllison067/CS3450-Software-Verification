#include <stdio.h>

//A signed integer in C is a data type that can hold values ranging from - 2, 147, 483, 648 to 2, 147, 483, 647.
//If the value held by the signed integer variable is 2, 147, 483, 647, and a 1 is added to it, it flips from positive
//to negative before looping aroundand returning to - 2, 147, 483, 648. An infinite loop may be created if you use a signed
//integerand expect it to act as an unsigned integer.For example, if you’re using an int variable to loop from 0 to 3000000000:
int main()
{
    int x;

    for (x = 0; x <= 3000000000; x++)
        printf("%d ", x);
    putchar('\n');

    return(0);
}