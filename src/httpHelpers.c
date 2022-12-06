#include "httpHelpers.h"

size_t cb(char *data, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    http_response *mem = (http_response *) userp;
    mem->response = realloc(mem->response, realsize);
    printf("cb: %s", data);
    strcpy(mem->response, data);
    mem->size = realsize;

    return realsize;
}
