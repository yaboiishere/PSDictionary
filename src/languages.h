typedef struct Language {
  char *code;
  char *name;
  int id;
} language;

typedef struct Languages {
  language *languages;
  int count;
} languages;

typedef struct SelectedLanguage {
  int from_id;
  int to_id;
} selected_language;

languages *get_languages();
selected_language *swap_languages(selected_language *);
