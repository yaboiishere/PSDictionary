typedef struct Language {
  char code[10];
  char name[50];
} language;

typedef struct Languages {
  language *languages;
  int count;
} languages;
