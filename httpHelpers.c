#include "httpHelpers.h"

size_t cb(void *data, size_t size, size_t nmemb, void *userp) {
  size_t realsize = size * nmemb;
  http_response *mem = (http_response *)userp;

  char *ptr = realloc(mem->response, mem->size + realsize + 1);
  if (ptr == NULL)
    return 0; /* out of memory! */

  mem->response = ptr;
  memcpy(&(mem->response[mem->size]), data, realsize);
  mem->size += realsize;
  mem->response[mem->size] = 0;

  return realsize;
}
