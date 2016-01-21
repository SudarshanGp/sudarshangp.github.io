//2. Fix the following multithreaded code. remove() should never allow the account to go negative.
pthread_mutex_t m; 
pthread_cond_t cv;
int money = 100;
void init() { money = 100;

  pthread_cond_init(&cv,NULL);
  pthread_mutex_init(&m, NULL);  
}
void add(int amount) {
  pthread_mutex_lock(&m);
  money += amount; 
  pthread_cond_broadcast(&cv); // wake up all blocked threads
  pthread_mutex_unlock(&m);
}

int remove(int amount) {
  pthread_mutex_lock(&m);
  
  while(money < amount) {
     pthread_cond_wait(&cv, &m); // remember unlock(m), blocks... then lock(m) before returning
  }
  money -= amount;
  int result = money;
  pthread_mutex_unlock(&m);
  return result;  // result can be out of date by the time we return.
}

----
typedef struct sem_t {
  int pizza;
  pthread_mutex_t m;
  pthread_cond_t cv;
} sem_t;
￼
sem_init(sem_t *s, int shared, int value) {
  s->pizza = value;
  pthread_cond_init(&s->cv,NULL);
  pthread_mutex_init(&s->m, NULL);
}
￼
￼

sem_post(sem_t*s) {
  pthread_mutex_lock(&m);
  s->pizza++;
  if( s->pizza ==1) { // only need to signal if we've incremented the count to 1. Why? :-)
    pthread_cond_signal(&cv); // Why is signal not broadcast OK for this specific problem?
  }
  pthread_mutex_unlock(&m);
}
sem_wait(sem_t*s) {
  pthread_mutex_lock(&m);
  while( s->pizza <=0) {
    pthread_cond_wait(&cv, &m);
  }
  s->pizza --;
  pthread_mutex_unlock(&m);
}  