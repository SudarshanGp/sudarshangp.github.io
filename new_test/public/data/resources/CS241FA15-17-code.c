pthread_mutex_t m;
pthread_cond_t cv;

#define N (16)
int remain = N;

double data[256][8192] ; 
int main() {
/* code to initialize the data values */ 
  pthread_mutex_init(&m, NULL);
  pthread_cond_init(&cv, NULL);
  pthread_t ids[N];
  for(int i=0;i<N;i++) pthread_create( ids + i, NULL , calc, (void*) i ); // Wait for all threads to finish
  
  for(int i=0;i<N;i++) pthread_join(ids[i], NULL);
  
/* code to print out result*/ }

void *calc( void* ptr ) {
/* Divide matrix work up into blocks of 16 columns. */
  int x,y, start = 16 * (int) ptr;
  int end = start + 16;
  for(x = start; x<end;x++) for(y=0; y <8192;y++) /* do calc #1 */ 
  // Wait until all threads have finished calc #1.

  pthread_mutex_lock(&m);
  remain --;
  if(remain ==0) pthread_cond_broadcast(&cv); // I'm the last thread to get here
  
  while(remain >0) pthread_cond_wait(&cv, &m); // Remember we unlock the mutex but will need to lock it before returning
  
  pthread_cond_unlock(&m)

  for(x = start; x<end;x++) for(y=0; y <8192;y++) /* do calc #2 */
￼￼return "Hello"; 
}