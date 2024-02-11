#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

void my_handler(int nsig){
    printf("Receive signal %d, %s\n", nsig, strsignal(nsig));
    fflush(stdout);
}

int main(void){
    printf("PID: %d\n", getpid());
    printf("SIGRTMAX: %d\nSIGKILL: %d\nSIGSTOP: %d\n", SIGRTMAX, SIGKILL, SIGSTOP);
    fflush(stdout);
    for(int i = 1; i <= SIGRTMAX; i++){
        signal(i, my_handler);
    }
    while(1);
    return 0;
}
