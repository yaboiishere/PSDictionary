typedef struct Language {
  char *code;
  char *name;
} language;

typedef struct Languages {
  language *languages;
  int count;
} languages;
