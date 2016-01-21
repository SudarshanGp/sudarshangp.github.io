#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>

pid_t childid; // Global variable to share between main and parent

void child() {
    
    alarm(1); // Make the alarm go in 1 second
    sleep(2);
    puts("I'm the child exiting normally"); // never happens
    exit(0);
}

void parent() {
    int status;
    waitpid(childid, &status, 0);
    if(WIFSIGNALED (status)) {
        printf("Child exited due to signal %d\n", WTERMSIG(status));
        if(WTERMSIG (status) == SIGALRM)
        puts("ALARM CLOCK");
    }else
    if( WIFEXITED(status)) {
        printf("Child exited with %d\n", WEXITSTATUS(status));
    }
}

int main() {
    printf("Hello world!\n");
    
    childid = fork ();
    if( childid > 0) parent();
    else if( childid == 0) child();
    else puts ("fork failed"); // print error
    
    return 0;
}

//-----
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
    

// Why 16 dots?
int main1(int argc, char* argv[]) {
    fork();
    fork();
    fork();
    int x = 0;
    alarm(2);
    while(x++ < 60) {
       char *mesg = "." 
       write(1, mesg , 1 );
       sleep(1);
    }
    return x;
}

int main2(int argc, char* argv[]) {
    char* args[] = {"sleep","10", NULL};
    execvp("sleep", args);
    
    // a simple fork bomb!
    // while(1) fork();
    
    puts( argv[0]); // name of the executable
    printf("%p\n",argv[argc]);
    return 0;
}

int main3(int argc, char* argv[]) {
    char buffer[1024];
    
    puts("Enter Your command oh master and I will exec it. Lol catz");
    while(1) {
        // bad bad bad - assume fgets always succeeds and writes a real non-zero-length string
        fgets(buffer, sizeof(buffer), stdin);

        buffer[ strlen(buffer)-1] = '\0'; // Danger! What if strlen returned zero

        char* args[]= {buffer, ".",NULL};
        if(fork() == 0 ) {
            execvp(buffer, args); // replace the shell
            perror("AHGSDHASGD");
        }
    }
    return 0;
}

