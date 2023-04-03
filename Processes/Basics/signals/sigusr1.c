#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int x = 0;

void handle_sigusr(int sig) {
    if (x == 0) {
        printf("First....!\n");
    }
}

int main(int argc, char* argv[]) {
    int pid = fork();
    if (pid == -1) {
        return 1;
    }
    
    if (pid == 0) {
        // Child process
        sleep(5);
        kill(getppid(), SIGUSR1);
    } else {
        // Parent process
        struct sigaction sa;
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = &handle_sigusr;
        sigaction(SIGUSR1, &sa, NULL);
        
        printf("What is 10-9: ");
        scanf("%d\n", &x);
        kill(pid,SIGKILL);
        if (x == 1) {
            printf("Right!\n");
        } else {
            printf("Wrong\n");
        }
        wait(NULL);
    }
    return 0;
}