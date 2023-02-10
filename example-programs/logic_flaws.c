#include<stdio.h> 

int main() {
	int x = 2;
	int y = 3;

	//assignemnt or equality check?
	if (x = y) {
		printf("potential bug");
	}
}