#include "languages.h"

#include <stdlib.h>

selected_language *swap_languages(selected_language *selected_languages) {
  language *tmp = selected_languages->from;
  selected_languages->from = selected_languages->to;
  selected_languages->to = tmp;
  return selected_languages;
}

languages *get_languages() {
  languages *langs = malloc(sizeof(languages));
  langs->count = 27;
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
  langs->languages[5].code = "EL";
  langs->languages[5].name = "Greek";
  langs->languages[5].id = 5;
  langs->languages[6].code = "ES";
  langs->languages[6].name = "Spanish";
  langs->languages[6].id = 6;
  langs->languages[7].code = "ET";
  langs->languages[7].name = "Estonian";
  langs->languages[7].id = 7;
  langs->languages[8].code = "FI";
  langs->languages[8].name = "Finnish";
  langs->languages[8].id = 8;
  langs->languages[9].code = "FR";
  langs->languages[9].name = "French";
  langs->languages[9].id = 9;
  langs->languages[10].code = "HU";
  langs->languages[10].name = "Hungarian";
  langs->languages[10].id = 10;
  langs->languages[11].code = "ID";
  langs->languages[11].name = "Indonesian";
  langs->languages[11].id = 11;
  langs->languages[12].code = "IT";
  langs->languages[12].name = "Italian";
  langs->languages[12].id = 12;
  langs->languages[13].code = "JA";
  langs->languages[13].name = "Japanese";
  langs->languages[13].id = 13;
  langs->languages[14].code = "LT";
  langs->languages[14].name = "Lithuanian";
  langs->languages[14].id = 14;
  langs->languages[15].code = "LV";
  langs->languages[15].name = "Latvian";
  langs->languages[15].id = 15;
  langs->languages[16].code = "NL";
  langs->languages[16].name = "Dutch";
  langs->languages[16].id = 16;
  langs->languages[17].code = "PL";
  langs->languages[17].name = "Polish";
  langs->languages[17].id = 17;
  langs->languages[18].code = "PT";
  langs->languages[18].name = "Portuguese";
  langs->languages[18].id = 18;
  langs->languages[19].code = "RO";
  langs->languages[19].name = "Romanian";
  langs->languages[19].id = 19;
  langs->languages[20].code = "RU";
  langs->languages[20].name = "Russian";
  langs->languages[20].id = 20;
  langs->languages[21].code = "SK";
  langs->languages[21].name = "Slovak";
  langs->languages[21].id = 21;
  langs->languages[22].code = "SL";
  langs->languages[22].name = "Slovenian";
  langs->languages[22].id = 22;
  langs->languages[23].code = "SV";
  langs->languages[23].name = "Swedish";
  langs->languages[23].id = 23;
  langs->languages[24].code = "TR";
  langs->languages[24].name = "Turkish";
  langs->languages[24].id = 24;
  langs->languages[25].code = "UK";
  langs->languages[25].name = "Ukrainian";
  langs->languages[25].id = 25;
  langs->languages[26].code = "ZH";
  langs->languages[26].name = "Chinese";
  langs->languages[26].id = 26;

  return langs;
}
