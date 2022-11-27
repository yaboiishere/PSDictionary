#include "httpHelpers.h"
#include "languages.h"
#include <curl/curl.h>
#include <json-c/json_object.h>
#include <json-c/json_tokener.h>
#include <stdlib.h>

languages parse_languages_json(char *);
http_response get_languages(char *);
languages get_languages_list(char *);
