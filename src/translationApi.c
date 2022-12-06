#include "translationApi.h"

const char *translate(const char *api_auth, const char *raw_test,
                      selected_language *selected_language) {
    CURL *curl = curl_easy_init();
    if (curl) {
        char *cleaned_text = curl_escape(raw_test, 0);

        http_response chunk = {.response = NULL, .size = 0};
        int str_len = strlen(cleaned_text) +
                      strlen("https://api-free.deepl.com/v2/translate?text=&target_lang=&source_lang=") +
                      strlen(selected_language->to->code) + strlen(selected_language->from->code) + 1;

        char *post_data = calloc(str_len, sizeof(char));

        strcpy(post_data, "https://api-free.deepl.com/v2/translate?text=");
        strcat(post_data, cleaned_text);
        strcat(post_data, "&target_lang=");
        strcat(post_data, selected_language->to->code);
        strcat(post_data, "&source_lang=");
        strcat(post_data, selected_language->from->code);

        curl_easy_setopt(curl, CURLOPT_URL, post_data);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);

        char *auth = calloc(strlen(api_auth) + strlen("Authorization: "), sizeof(char));
        strcat(auth, "Authorization: ");
        strcat(auth, api_auth);

        printf("auth: %s", auth);

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, auth);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s",
                    curl_easy_strerror(res));
            return curl_easy_strerror(res);
        }

        while (chunk.response[0] == '\000') {
            printf("waiting for response");
        }

        json_object *jobj = json_tokener_parse(chunk.response);
        json_object *translations;
        json_object_object_get_ex(jobj, "translations", &translations);
        json_object *translation = json_object_array_get_idx(translations, 0);
        json_object *text;
        json_object_object_get_ex(translation, "text", &text);
        char *resp = (char *) json_object_get_string(text);
        char *output = calloc(strlen(resp), sizeof(char));
        strcpy(output, resp);

        curl_free(cleaned_text);
        free(post_data);
        free(auth);
        free(chunk.response);
        curl_easy_cleanup(curl);
        return output;
    }

    return "Error starting CURL";
}
