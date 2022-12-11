#include "httpHelpers.h"
#include "languages.h"
#include <curl/curl.h>
#include "../include/json-c/json_object.h"
#include "../include/json-c/json_tokener.h"
#include <stdlib.h>

const char *translate(CURL *, const char *, const char *, selected_language *, languages *);
