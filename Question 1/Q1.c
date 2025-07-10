// q1_exec.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <command>\n", argv[0]);
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process: execute the command
        execvp(argv[1], &argv[1]);
        perror("execvp failed");
        exit(1);
    } else {
        // Parent process: create temp file, write and read
        int fd = open("tempfile.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
        if (fd < 0) {
            perror("open failed");
            return 1;
        }

        const char *msg = "This is a temporary file.\n";
        if (write(fd, msg, strlen(msg)) < 0) {
            perror("write failed");
            close(fd);
            return 1;
        }

        // Rewind file offset to read
        lseek(fd, 0, SEEK_SET);

        char buf[100];
        ssize_t n = read(fd, buf, sizeof(buf)-1);
        if (n < 0) {
            perror("read failed");
            close(fd);
            return 1;
        }
        buf[n] = '\0';
        printf("Read from tempfile: %s", buf);

        close(fd);

        // Wait for child to finish
        wait(NULL);
    }

    return 0;
}
