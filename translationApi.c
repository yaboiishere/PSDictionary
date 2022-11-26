#include "translationApi.h"

json_object *getLanguages(char *api_key) {
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

  CURLcode ret = curl_easy_perform(hnd);
}
