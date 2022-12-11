#include <curl/curl.h>
#include "../include/json-c/json_object.h"
#include "../include/json-c/json_tokener.h"
#include "languages.h"
#include <stdlib.h>
#include "httpHelpers.h"
#include "files.h"

typedef struct translationHolder {
   char *translation;
} translation_holder;

const char *translate(CURL *, const char *, const char *, selected_language *, languages *);
translation_holder* translate_arr(CURL *, const char *, file_type, selected_language*, languages *);
file_type convert_to_file_type(translation_holder*, int);