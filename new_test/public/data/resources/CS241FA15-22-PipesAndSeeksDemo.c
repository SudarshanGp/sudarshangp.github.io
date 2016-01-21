/*Write your C code here*/
#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void hey(int signal) {
    write(1,"Hey\n",4);
}

int main() {
    int filedes[2];
    signal(SIGPIPE,hey);
    
    pipe( filedes );
    sleep(1);
    exit(0);
    pid_t child = fork();
    if(child > 0) { 
        /* I must be the parent */
        char buffer[80];
        int bytesread = read(filedes[0] , buffer, sizeof(buffer));
        write(1, buffer, bytesread);
        // do something with the bytes read
    } else {
        //fdopen(int fd, const char *mode);
        FILE* f = fdopen(filedes[1],"w");
        fprintf(f,"Hi!\n");
    }
    sleep(1);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    FILE* f = fopen("data.csv","w");
    
    fprintf(f,"123\n");
    
    fseek(f,0,SEEK_END);
    long size = ftell(f);
    printf("%d bytes\n",(int) size);
    if(fork()) {
        fseek(f,0,SEEK_SET);
        
        fclose(f);
    } else {
        sleep(1);
        fprintf(f,"BigOne at %d!\n",getpid());
        fclose(f);
    }
    return 0;
}

