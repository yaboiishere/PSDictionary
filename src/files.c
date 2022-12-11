#include "files.h"

file_type read_file(char *filename) {
    FILE *fp;
    int line_count = 0;

    fp = fopen(filename, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    char *line = NULL;
    size_t len = 0;
    while ((getline(&line, &len, fp)) != -1) {
        line_count++;
    }
    rewind(fp);

    char **lines = malloc(sizeof(char *) * line_count);

    ssize_t read;
    int i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        lines[i] = malloc((sizeof(char) * read)-1);
        strcpy(lines[i], line);
        i++;
    }

    fclose(fp);
    if (line)
        free(line);
    return (file_type) {.lines = lines, .line_count = line_count};
}

int write_file(char *filename, char **translations, int line_count) {
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    for (int i = 0; i < line_count; i++) {
        fprintf(fp, "%s", translations[i]);
    }

    fclose(fp);
    return 0;
}