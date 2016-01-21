#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <semaphore.h>

sem_t s;

void myhandler(int signal)
{
    sem_post(&s); // post a free pizza slice to our semaphre! 
    // be good - No printf-ing inside the signal handler.
    // sem_post is one of the few functions that can safely be called inside a signal handler
}

/
void *cleanupthread(void *param)
{
    sem_wait(&s); // We wait to eat one pizza slice
    printf("Yo ho ho ho a pirates life for me!\n");
    
    return NULL;
}

int main()
{
    // unnamed semaphores are unsupported by OSX!
    // Create a semaphore with zero pizza slices - our singsong method will be forced to wait...
    
    if( sem_init(&s, 0, 0) == -1) {
       perror("sem_init failed-are you on a Mac?"); 
       return 1;
    }

    // Cheat here (we should be using sigaction() in a mulithreaded program)
    signal(SIGINT, myhandler);

    // Create the clean up thread. It wont clean up until the sem_post is called at least once
    pthread_t tid;
    pthread_create(&tid, NULL, cleanupthread, NULL);
    pthread_exit(NULL);
}
