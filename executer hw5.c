#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        int fd[2];

        if (pipe(fd) == -1) {
            return 1;
        }

        pid_t pid1 = fork();

        if (pid1 == -1) {
            return 1;
        }

        if (pid1 == 0) {
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);

            execl("/bin/sh", "sh", "-c", argv[i], NULL);
            exit(1);
        }

        pid_t pid2 = fork();

        if (pid2 == -1) {
            return 1;
        }

        if (pid2 == 0) {
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);

            execlp("wc", "wc", "-c", NULL);
            exit(1);
        }

        close(fd[0]);
        close(fd[1]);

        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
    }

    return 0;
}
