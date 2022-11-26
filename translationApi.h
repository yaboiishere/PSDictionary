#include "languages.h"
#include <json-c/json_object.h>

Language parseLanguagesJson(json_object *jsonLanguage);
json_object *getLanguages(char *apiKey);
