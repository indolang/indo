#include <stdio.h>
#include "parser.h"
#include "runtime.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: indo <file.idn>\n");
        return 1;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "r");

    if (!file) {
        perror("File error");
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        parse_line(line);
    }

    fclose(file);
    return 0;
}
