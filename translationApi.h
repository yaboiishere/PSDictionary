#include "httpHelpers.h"
#include "languages.h"
#include <curl/curl.h>
#include <json-c/json_object.h>
#include <json-c/json_tokener.h>
#include <stdlib.h>

const char *translate(const char *, const char *, selected_language *);
