#include "translationApi.h"

const char *translate(const char *api_auth, const char *text,
                      selected_language *selected_language) {
  //curl -X POST 'https://api-free.deepl.com/v2/translate' \
	-H 'Authorization: DeepL-Auth-Key fd404e0d-8d73-67df-bea9-db9d40bb6672:fx' \
	-d 'text=Hello%2C%20world!' \
	-d 'target_lang=DE'

  //{
  /* "translations": [ */
  /*   { */
  /*     "detected_source_language": "EN", */
  /*     "text": "Hallo, Welt!" */
  /*   } */
  /* ] */
  /* } */

  // call api and get text from response
  printf("translate: %s", text);
  char *output;
  http_response chunk = {0};
  CURL *curl = curl_easy_init();
  if (curl) {
    printf("curl init");
    int str_len = strlen(text) + strlen("text=&target_lang=") +
                  strlen(selected_language->to->code) + 1;

    char *post_data = malloc(str_len);

    strcpy(post_data, "text=");
    strcat(post_data, text);
    strcat(post_data, "&target_lang=");
    strcat(post_data, selected_language->to->code);

    curl_easy_setopt(curl, CURLOPT_URL,
                     "https://api-free.deepl.com/v2/translate");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);
    curl_easy_setopt(curl, CURLAUTH_BEARER, api_auth);
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s",
              curl_easy_strerror(res));
      return "error";
    }

    json_object *jobj = json_tokener_parse(chunk.response);
    json_object *translations;
    json_object_object_get_ex(jobj, "translations", &translations);
    json_object *translation = json_object_array_get_idx(translations, 0);
    json_object *text;
    json_object_object_get_ex(translation, "text", &text);
    strcpy(output, json_object_get_string(text));
  }
  curl_easy_cleanup(curl);

  return output;
}
