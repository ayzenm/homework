#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        return 1;
    }

    char *pattern = argv[1];
    char *text = argv[2];
    char *replacement = argv[3];

    regex_t regex;
    regmatch_t match;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return 1;
    }

    size_t size = strlen(text) + 1;
    char *result = (char *)malloc(size);

    if (result == NULL) {
        regfree(&regex);
        return 1;
    }

    result[0] = '\0';

    char *current = text;

    while (regexec(&regex, current, 1, &match, 0) == 0) {
        size_t before = match.rm_so;

        size_t new_size = strlen(result)
                        + before
                        + strlen(replacement)
                        + strlen(current + match.rm_eo)
                        + 1;

        result = (char *)realloc(result, new_size);
        if (result == NULL) {
            regfree(&regex);
            return 1;
        }

        strncat(result, current, before);
        strcat(result, replacement);

        current += match.rm_eo;
    }

    strcat(result, current);

    printf("%s\n", result);

    free(result);
    regfree(&regex);

    return 0;
}
