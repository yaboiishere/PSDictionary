#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
  char *response;
  size_t size;
} http_response;

size_t cb(char *, size_t, size_t, void *);
