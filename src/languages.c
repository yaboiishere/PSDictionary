#include "languages.h"

#include <stdlib.h>

selected_language *swap_languages(selected_language *selected_languages) {
  int tmp = selected_languages->from_id;
  selected_languages->from_id = selected_languages->to_id;
  selected_languages->to_id = tmp;
  return selected_languages;
}

languages *get_languages() {
  languages *langs = malloc(sizeof(languages));
  langs->count = 17;
  langs->languages = malloc(sizeof(language) * langs->count);
  langs->languages[0].code = "EN";
  langs->languages[0].name = "English";
  langs->languages[0].id = 0;
  langs->languages[1].code = "BG";
  langs->languages[1].name = "Bulgarian";
  langs->languages[1].id = 1;
  langs->languages[2].code = "CS";
  langs->languages[2].name = "Czech";
  langs->languages[2].id = 2;
  langs->languages[3].code = "DA";
  langs->languages[3].name = "Danish";
  langs->languages[3].id = 3;
  langs->languages[4].code = "DE";
  langs->languages[4].name = "German";
  langs->languages[4].id = 4;
  langs->languages[5].code = "ES";
  langs->languages[5].name = "Spanish";
  langs->languages[5].id = 5;
  langs->languages[6].code = "FR";
  langs->languages[6].name = "French";
  langs->languages[6].id = 6;
  langs->languages[7].code = "ID";
  langs->languages[7].name = "Indonesian";
  langs->languages[7].id = 7;
  langs->languages[8].code = "IT";
  langs->languages[8].name = "Italian";
  langs->languages[8].id = 8;
  langs->languages[9].code = "LT";
  langs->languages[9].name = "Lithuanian";
  langs->languages[9].id = 9;
  langs->languages[10].code = "NL";
  langs->languages[10].name = "Dutch";
  langs->languages[10].id = 10;
  langs->languages[11].code = "PT";
  langs->languages[11].name = "Portuguese";
  langs->languages[11].id = 11;
  langs->languages[12].code = "RO";
  langs->languages[12].name = "Romanian";
  langs->languages[12].id = 12;
  langs->languages[13].code = "RU";
  langs->languages[13].name = "Russian";
  langs->languages[13].id = 13;
  langs->languages[14].code = "SK";
  langs->languages[14].name = "Slovak";
  langs->languages[14].id = 14;
  langs->languages[15].code = "SL";
  langs->languages[15].name = "Slovenian";
  langs->languages[15].id = 15;
  langs->languages[16].code = "SV";
  langs->languages[16].name = "Swedish";
  langs->languages[16].id = 16;
  langs->languages[17].code = "TR";
  langs->languages[17].name = "Turkish";
  langs->languages[17].id = 17;

  return langs;
}
