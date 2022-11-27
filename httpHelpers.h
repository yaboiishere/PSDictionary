#include <stdlib.h>
#include <string.h>

typedef struct {
  int resp_code;
  char *response;
  size_t size;
} http_response;

size_t cb(void *, size_t, size_t, void *);
