#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 2) {
        write(2, "Wrong arguments\n", 16);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    struct stat st;
    fstat(fd, &st);

    off_t middle = st.st_size / 2;
    lseek(fd, middle, SEEK_SET);

    char buf[BUF_SIZE];
    ssize_t bytes;

    while ((bytes = read(fd, buf, BUF_SIZE)) > 0) {
        for (int i = 0; i < bytes; i++) {
            write(1, &buf[i], 1);

            if (buf[i] == '\n') {
                close(fd);
                return 0;
            }
        }
    }

    close(fd);
    return 0;
}
