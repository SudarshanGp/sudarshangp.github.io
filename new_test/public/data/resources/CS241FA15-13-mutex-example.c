#include <stdio.h>
#include <pthread.h>
// Compile with -pthread
// Create a mutex this ready to be locked!
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

int sum = 0;

void *countgold(void *param)
{
    int i;
//Same thread that locks the mutex must unlock it
//Critical section is just 'sum+=1'
//However locking and unlocking a million times
//has significant overhead in this simple answer
//
// Other threads that call lock will have to wait until we call unlock

// Remember: ONLY ONE THREAD CAN PROCEED when it attempts to lock a particular mutex
// The other must wait until the lock is unlocked before it can continue (and lock the mutex itself)
// Thus - only one thread at a time will be in the CRITICAL SECTION ("CS")

// 4 Gotchas: initialize your mutexes beforehand; don't double lock in the same thread; unlock in same thread; only destroy unlocked; 

// We could also use a counting semaphore (eat 1 pizza slice before the CRITICAL SECTION
// donate 1 slice afterwards; and start with a pizza box with just one slice available)

    for (i = 0; i < 10000000; i++) {
      pthread_mutex_lock(&m);
      sem_wait(&s);
      sum += 1; // CRITICAL SECTION
    sem_post(&s);
      pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main()
{
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, countgold, NULL);
    pthread_create(&tid2, NULL, countgold, NULL);
//Wait for both threads to finish:
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
// Only destroy mutex once (and never destroy a locked mutex)
    pthread_mutex_destroy(&m);

    printf("ARRRRG sum is %d\n", sum);
    return 0;
}


#if 0 
// Thread-safe stack example
float *array
int counter

p_m_t m1 = PTHREAD_MUTEX_INITIALIZER

void push(float v) {
  p_m_lock(&m1)
  array[counter] = v;
  counter ++;
  p_m_unlock(&m1)
}

float pop() {
  p_m_lock(&m1)
  counter --;
  float result = array[counter];
  p_m_unlock(&m1)
  return result;
}
#endif