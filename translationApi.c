#include "translationApi.h"

http_response get_languages(char *api_key) {
  CURL *hnd = curl_easy_init();

  curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
  curl_easy_setopt(
      hnd, CURLOPT_URL,
      "https://google-translate1.p.rapidapi.com/language/translate/v2");

  struct curl_slist *headers = NULL;
  headers = curl_slist_append(
      headers, "content-type: application/x-www-form-urlencoded");
  headers = curl_slist_append(headers, "Accept-Encoding: application/gzip");
  headers = curl_slist_append(
      headers,
      "X-RapidAPI-Key: 9d3a40bd7dmsh6b8cb6443d1f4b1p1835afjsn1e8c635d40ca");
  headers = curl_slist_append(
      headers, "X-RapidAPI-Host: google-translate1.p.rapidapi.com");
  curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS,
                   "q=Hello%2C%20world!&target=es&source=en");

  http_response chunk = {.size = 0};
  curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &chunk);
  curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, cb);

  CURLcode ret = curl_easy_perform(hnd);
  if (ret) {
    const char *maybe_error = curl_easy_strerror(ret);
    chunk.response = (char *)maybe_error;
    chunk.resp_code = ret;
  }

  return chunk;
}

languages parse_languages_json(char *raw_json) {
  language *languages_arr = calloc(140, sizeof(language));
  struct json_object *json = json_tokener_parse(raw_json);
  json_object *data = json_object_object_get(json, "data");
  json_object *langs = json_object_object_get(data, "languages");
  int i = 0, languages_count = json_object_array_length(langs);
  for (i = 0; i < languages_count; i++) {
    json_object *lang = json_object_array_get_idx(langs, i);
    json_object *name = json_object_object_get(lang, "name");
    json_object *code = json_object_object_get(lang, "language");
    languages_arr[i].name = (char *)json_object_get_string(name);
    languages_arr[i].code = (char *)json_object_get_string(code);
  }
  languages langs_struct = {.languages = languages_arr,
                            .count = languages_count};
  return langs_struct;
}

languages get_languages_list(char *api_key) {
  http_response resp = get_languages(api_key);
  languages langs = parse_languages_json(resp.response);
  return langs;
}
