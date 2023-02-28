#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int g;

void *thread (void *arg) {
  g = 2;
}

int main() {
  pthread_t id1;
  pthread_create(&id1, NULL, thread, NULL);
  g = 1;
  // this may fail
  assert(g==1);
  exit(0);
}  

/*
  cbmc example-programs/threads.c - will generate one assertion failure,
  fixed by joining thread before g = 1
  
*/