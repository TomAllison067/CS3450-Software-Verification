#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <limits.h>
/*
  This one is more about pointers than threads.

  Good: malloc a ptr, set its id
  cbmc example-programs/threads_segmentationfault.c --pointer-check passes
  The program can compile and run and doesn't segfault

  Bad:
  cbmc example-programs/threads_segmentationfault.c --pointer-check fails:
    example-programs/threads_segmentationfault.c function main
    [main.pointer_dereference.1] line 34 dereference failure: pointer NULL in ptr->id: FAILURE
    [main.pointer_dereference.2] line 34 dereference failure: pointer invalid in ptr->id: FAILURE
    [main.pointer_dereference.3] line 34 dereference failure: deallocated dynamic object in ptr->id: FAILURE
    [main.pointer_dereference.4] line 34 dereference failure: dead object in ptr->id: FAILURE
    [main.pointer_dereference.5] line 34 dereference failure: pointer outside object bounds in ptr->id: FAILURE
    [main.pointer_dereference.6] line 34 dereference failure: invalid integer address in ptr->id: FAILURE

  Program can compile and run but segfaults  

  If we use ptr array, "pointer handling for concurrency is unsound" unhelpful!
*/
int g;

void *thread (void *arg) {
  g = 2;
}

struct threadIdStruct {
  pthread_t id;
};

int main() {
  // GOOD
  int LARGE_NUMBER = 2;
  struct threadIdStruct array[LARGE_NUMBER];
  for (int i = 0; i <  LARGE_NUMBER; i++) {
    pthread_create(array[i].id, NULL, thread, NULL);
    printf("%ld\n", array[i].id);
  }
  for (int i = 0; i < LARGE_NUMBER; i++) {
    pthread_join(array[i].id, NULL);
  }
  
  g = 1;
  assert(g==1);
  exit(0);
}  

/*
  cbmc example-programs/threads.c - will generate one assertion failure,
  fixed by joining thread before g = 1

  Note - 
  
*/