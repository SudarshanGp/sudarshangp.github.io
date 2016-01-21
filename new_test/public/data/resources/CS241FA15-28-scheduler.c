// A simpler scheduler simulation by Lawrence Angrave 2015
// This is new code and only lightly tested
// but is sufficient for simple demonstrations
// gcc scheduler.c -std=c99 -g -o scheduler && ./scheduler -p sjf
/* Example output:
gcc scheduler.c -std=c99 -g -o scheduler && ./scheduler -p sjf
  0:P2
 10:P4
(P4 finished with wait time 0)
 20:P2
(P2 finished with wait time 10)
 30:P3
 40:P3
(P3 finished with wait time 30)
 50:P1
 60:P1
 70:P1
(P1 finished with wait time 50)

Total Wait:90, average:22.5
*/

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define NUMBER(x) (sizeof(x) / sizeof(x[0]))


 
typedef struct {
  char* name;
  int arrival;
  int execution;
  int priority;
  
} request_t; 

/* List jobs in order of arrival */
request_t requests[] = {
/*name, arrival, execution, priority */
{ "P1",  00 , 30 , 1},
{ "P2",  00 , 20 , 2},
{ "P3",  00 , 20 , 3},
{ "P4",  10 , 10 , 4}};

int n_requests = NUMBER(requests);

 typedef struct {
  int remain;
  int first;
  int started;
  int completed;
  
} stat_t;

stat_t * stats;
int time = 0;
int delta = 10;
int process = -1;

char* name;
int preemption ; 
int total_wait;
int remaining_processes = NUMBER(requests);
 
void update_stats() {
  if(process<0) return;
  assert(process <  n_requests);

  stat_t* s = &stats[process];
  assert(!s->completed);

  if(!s->started) {
    s->started = 1;
    s->first= time;
    s->remain = requests[process].execution;
  }
  s->remain -= delta;
  
  if( s->remain <=0) {   
    s->completed = 1;
    remaining_processes --; 
    int wait  = (time + delta) - requests[process].arrival - requests[process].execution;  
    printf("(%s finished with wait time %d)\n", name, wait);
    total_wait +=  wait;
  }
}

// skip completed jobs and jobs that are in the future  
int can_run(int i) {
  if( i < 0 || i >= n_requests ) return 0;
     
  return ! stats[i].completed &&  requests[i].arrival <= time;
}

// Trick/Limitation: Use the original request as the queue because the job sequence cannot be changed.
// This assumes the jobs are listed in arrival order 
void round_robin() {
  int check =  n_requests ;
  do { 
    process = (process + 1) %  n_requests;
  } while(  check -- && ! can_run(process) );
  
  if(!check)
    process = -1; /* No process can be scheduled */
}

void shortest_job_first() {                           
  // Not pre-emptive so continue to run an existing to completion:
  if( ! preemption && can_run(process) ) return;
  // RUle #2 Find a new shortest job 
  
  process = -1;
  for(int i = 0; i < n_requests;i++) {
    if( ! ! can_run(i) ) 
      if( process == -1 || requests[i].execution < requests[process].execution ) 
        process = i;                        
  }
}

void priority() {                           
  // Not pre-emptive so continue to run an existing to completion:
  if( ! preemption && can_run(process) ) return;
  // RUle #2 Find a new highest priority 

  process = -1;
  for(int i = 0; i < n_requests;i++) {
    if( can_run(i) ) 
      if( process == -1 || requests[i].priority > requests[process].priority ) 
        process = i;                        
  }
}

void first_come_first_served() {
  // Not pre-emptive so continue to run an existing to completion:
  if( process>=0 && can_run(process) ) return; 

  process = -1;
  for(int i = 0; i < n_requests;i++) {
    if( can_run(i) ) 
      if( process == -1 || requests[i].arrival < requests[process].arrival ) 
        process = i;                        
  }  
}

typedef void (*scheduler_fn) ();

typedef struct {
  char* name;
  char* shortname;
  scheduler_fn fn;
} named_scheduler_t;    

named_scheduler_t schedulers[] = {  
  {"roundrobin","rr",round_robin},
  {"firstcomefirstserved","fcfs",first_come_first_served}, 
  {"shortestjobfirst","sjf",shortest_job_first},  
  {"priority","pri",shortest_job_first},  
}; 

scheduler_fn to_sched(char*name) {
  if(!name ) return NULL;
  for(int i = 0; i < NUMBER(schedulers);i++)
    if(!strcmp(name, schedulers[i].name) || !strcmp(name, schedulers[i].shortname))
      return schedulers[i].fn; 
  return NULL;
}


int main(int argc, char**argv) {
  char* schedname = argc > 1 ? argv[argc -1 ] :"";
  char* options = argc > 2? argv[1] : NULL;
  preemption = options && strchr(options,'p');
  
  scheduler_fn schedule = to_sched(schedname);  
  
  if(preemption && (schedule == first_come_first_served || schedule == round_robin)) 
     schedule = NULL; /* Force usage message */
     
  if(!schedule) fprintf(stderr, "Usage %s: [p] rr|fcfs|sjf|priority\n  p : enable pre-emptive scheduling for sjf & priority\n", argv[0]) , exit(1);
  
  stats = calloc(sizeof(stat_t), n_requests);
    
  while( remaining_processes >0 ) {
    
    schedule();

    name = process < 0 ? "-": requests[process].name;      
    
    printf("%3d:%s\n", time, name);
    
    update_stats();

    time += delta;
  }
  double average_wait = total_wait / (double) n_requests;
  printf("\nTotal Wait:%d, average:%.3g\n", total_wait, average_wait);
}

