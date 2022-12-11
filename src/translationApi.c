#include "translationApi.h"

const char *translate(CURL *curl, const char *api_auth, const char *raw_test,
                      selected_language *selected_language, languages *languages) {
    if (curl) {
        char *cleaned_text = curl_escape(raw_test, 0);

        http_response chunk = {.response = NULL, .size = 0};
        int str_len = strlen(cleaned_text) +
                      strlen("https://api-free.deepl.com/v2/translate?text=&target_lang=&source_lang=") +
                      4 + 1;

        char *post_data = calloc(str_len, sizeof(char));

        char *to_lang = languages->languages[selected_language->to_id].code;
        char *from_lang = languages->languages[selected_language->from_id].code;

        strcpy(post_data, "https://api-free.deepl.com/v2/translate?text=");
        strcat(post_data, cleaned_text);
        strcat(post_data, "&target_lang=");
        strcat(post_data, to_lang);
        strcat(post_data, "&source_lang=");
        strcat(post_data, from_lang);

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
        char *output = malloc(strlen(resp) * sizeof(char) + 1);
        strcpy(output, resp);

        free(post_data);
        free(auth);
        return output;
    }
    return "Error starting CURL";
}

translation_holder *
translate_arr(CURL *curl, const char *api_key, file_type file_data, selected_language *selected_language,
              languages *languages) {
    translation_holder *output = malloc(sizeof(translation_holder) * file_data.line_count);
    for (int i = 0; i < file_data.line_count; i++) {
        output[i].translation = translate(curl, api_key, file_data.lines[i], selected_language, languages);
    }
    return output;
}

file_type convert_to_file_type(translation_holder* holders, int size){
    char** lines = malloc(sizeof(char*) * size);
    for(int i = 0; i < size; i++){
        lines[i] = holders[i].translation;
    }
    return (file_type){.lines = lines, .line_count = size};
}
