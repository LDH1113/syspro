#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid1, pid2;
    char buffer[100];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    printf("parent process start\n");

    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        close(pipefd[0]);
        printf("input string: ");
        fgets(buffer, sizeof(buffer), stdin);
        write(pipefd[1], buffer, strlen(buffer) + 1);
        close(pipefd[1]);
        exit(0);
    } else {
        pid2 = fork();
        if (pid2 == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid2 == 0) {
            close(pipefd[1]);
            read(pipefd[0], buffer, sizeof(buffer));
            for (int i = 0; buffer[i]; i++) {
                buffer[i] = toupper((unsigned char)buffer[i]);
            }
            printf("%s", buffer);
            close(pipefd[0]);
            exit(0);
        } else {
            close(pipefd[0]);
            close(pipefd[1]);
            wait(NULL);
            wait(NULL);
        }
    }

    return 0;
}

