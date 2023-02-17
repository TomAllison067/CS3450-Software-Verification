#include <stdio.h>

int end_loop = 1;
int count = 0;

int main() {
  while(end_loop) {
    printf(count);
    count++;
    if(count > 10){
        end_loop = 0;
    }
  }
}
