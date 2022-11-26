struct Language {
  char code[10];
  char name[50];
};

struct Languages {
  Language *languages;
  int count;
};
