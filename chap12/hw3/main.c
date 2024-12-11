#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

void execute_command(char *command) {
    char *argv[10];
    char *token;
    int i = 0;

    token = strtok(command, " ");
    while (token != NULL && i < 10) {
        argv[i++] = token;
        token = strtok(NULL, " ");
    }
    argv[i] = NULL;

    execvp(argv[0], argv);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        exit(EXIT_FAILURE);
    }

    char *pipe_pos = strchr(argv[1], '|');
    if (pipe_pos == NULL) {
        exit(EXIT_FAILURE);
    }

    *pipe_pos = '\0';
    char *command1 = argv[1];
    char *command2 = pipe_pos + 1;

    while (*command2 == ' ') {
        command2++;
    }

    command1[strcspn(command1, "\n")] = 0; 
    command2[strcspn(command2, "\n")] = 0; 

    int fd[2];
    if (pipe(fd) == -1) {
        exit(EXIT_FAILURE);
    }

    if (fork() == 0) {
        close(fd[READ]);
        dup2(fd[WRITE], STDOUT_FILENO);
        close(fd[WRITE]);
        execute_command(command1);
    } else if (fork() == 0) {
        close(fd[WRITE]);
        dup2(fd[READ], STDIN_FILENO);
        close(fd[READ]);
        execute_command(command2);
    } else {
        close(fd[READ]);
        close(fd[WRITE]);
        wait(NULL);
        wait(NULL);
    }

    return 0;
}

