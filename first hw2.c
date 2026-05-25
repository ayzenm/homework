#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 4) {
        write(2, "Wrong arguments\n", 16);
        return 1;
    }

    char *file_name = argv[1];
    int start = atoi(argv[2]);
    int count = atoi(argv[3]);

    int fd = open(file_name, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    struct stat st;
    fstat(fd, &st);

    int size = BUF_SIZE;
    if (st.st_size < BUF_SIZE && st.st_size > 0) {
        size = st.st_size;
    }

    char *buf = malloc(size);
    if (buf == NULL) {
        close(fd);
        return 1;
    }

    int line = 1;
    int printed = 0;
    int printing = 0;

    ssize_t bytes;

    while ((bytes = read(fd, buf, size)) > 0) {
        int begin = -1;

        for (int i = 0; i < bytes; i++) {
            if (line >= start && printed < count) {
                if (!printing) {
                    begin = i;
                    printing = 1;
                }
            }

            if (buf[i] == '\n') {
                if (line >= start && printed < count) {
                    write(1, buf + begin, i - begin + 1);
                    printed++;
                    printing = 0;
                }

                line++;

                if (printed == count) {
                    free(buf);
                    close(fd);
                    return 0;
                }
            }
        }

        if (printing && begin != -1) {
            write(1, buf + begin, bytes - begin);
        }
    }

    free(buf);
    close(fd);

    return 0;
}
