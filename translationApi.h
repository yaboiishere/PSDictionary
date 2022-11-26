#include "languages.h"
#include <curl/curl.h>
#include <json-c/json_object.h>

languages *parseLanguagesJson(json_object *);
json_object *getLanguages(char *);
