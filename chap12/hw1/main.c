#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[100];

    pipe(pipefd);
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(pipefd[1]);
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Recv: [%d] %s from PID [%d]\n", getppid(), buffer, getpid());
        close(pipefd[0]);
        exit(0);
    } else {
        close(pipefd[0]);
        sprintf(buffer, "Hello");
        printf("Send: [%d] %s from PID [%d]\n", getpid(), buffer, getpid());
        write(pipefd[1], buffer, strlen(buffer) + 1);
        close(pipefd[1]);
        wait(NULL);
    }

    return 0;
}

