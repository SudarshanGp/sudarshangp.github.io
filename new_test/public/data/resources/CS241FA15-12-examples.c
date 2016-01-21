#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Threads = "Allow two CPUs to work inside your process at the same time"
// include pthread.h
// compile with -pthread

int counter; // global

void* myfunc1(void*ptr) {
  int value = * (int*)ptr;
  printf("My thread id is %ld and I was given a pointer %p\n", (long) pthread_self(), ptr);
   printf("My thread id is %ld and I’m starting at %d\n", (long) pthread_self(), value);
   return NULL;
}

int main1() {
   // Each thread gets a different value of i to process
   pthread_t tid; 
   for(int i =0; i < 10; i++) {
     int* params = malloc(sizeof(int));
     *params = i;
      pthread_create(&tid, 0, myfunc1, params);
  }
  sleep(5);
  return 0;
}



int counter2;

void*myfunc2(void*param) {
  int i=0; // stack variable  - so local to each thread.
  for(; i < 1000000;i++) 
     counter2 ++;
  return NULL;
}

int main() {
  pthread_t tid1,tid2;
pthread_create(&tid1, 0, myfunc2, NULL);
pthread_join(tid1,NULL);
pthread_create(&tid2, 0, myfunc2, NULL);
pthread_join(tid2,NULL);
printf("%d\n", counter2 );
}











