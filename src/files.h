#ifndef FILES_H
#define FILES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct fileType{
    char **lines;
    int line_count;
} file_type;

file_type read_file(char *);

int write_file(char *, char**, int);
#endif