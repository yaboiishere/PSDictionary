#include <GL/glew.h>

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#include "deps/nuklear.h"
#include "deps/nuklear_glfw_gl3.h"
#include "translationApi.h"
#include <dotenv.h>

static void error_callback(int e, const char *d) {
  printf("Error %d: %s\n", e, d);
}

int main(void) {
  env_load(".", false);
  char *api_key = getenv("API_KEY");
  if (api_key == NULL) {
    printf("API_KEY is missing from .env file");
    return 1;
  }

  /* Platform */
  int win_width = 400;
  int win_height = 450;

  /* GLFW */
  struct nk_glfw glfw = {0};
  static GLFWwindow *win;
  glfwSetErrorCallback(error_callback);
  if (!glfwInit()) {
    fprintf(stdout, "[GFLW] failed to init!\n");
    exit(1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  win = glfwCreateWindow(win_width, win_height, "Dictionary", NULL, NULL);
  glfwMakeContextCurrent(win);

  /* Glew */
  glewExperimental = 1;
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to setup GLEW\n");
    exit(1);
  }

  /* create context */
  struct nk_context *ctx =
      nk_glfw3_init(&glfw, win, NK_GLFW3_INSTALL_CALLBACKS);

  {
    struct nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(&glfw, &atlas);
    nk_glfw3_font_stash_end(&glfw);
  }

  char buf[256] = {0};
  languages languages = get_languages_list(api_key);
  char *languages_names[languages.count];
  for (int i = 0; i < languages.count; i++) {
    languages_names[i] = languages.languages[i].name;
  }
  static int currentFromLang = 0;
  static int currentToLang = 1;
  static const float singleElementRatio[] = {0.2f, 0.6f, 0.2f};
  static const float tripleElementRatio[] = {0.1f, 0.6f, 0.3f};

  while (!glfwWindowShouldClose(win)) {
    /* Input */
    glfwPollEvents();
    nk_glfw3_new_frame(&glfw);

    /* GUI */
    if (nk_begin(ctx, "Dictionary", nk_rect(0, 0, win_width, win_height), 0)) {
      nk_layout_row_dynamic(ctx, 60, 1);
      nk_label(ctx, "Dictionary", NK_TEXT_CENTERED);

      nk_layout_row(ctx, NK_DYNAMIC, 30, 4, tripleElementRatio);
      nk_label(ctx, "Input:", NK_TEXT_LEFT);
      nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, buf, sizeof(buf) - 1,
                                     nk_filter_default);
      nk_combobox(ctx, languages_names, languages.count, &currentFromLang, 25,
                  nk_vec2(200, 200));
      nk_spacing(ctx, 1);

      nk_layout_row(ctx, NK_DYNAMIC, 30, 3, singleElementRatio);
      nk_spacing(ctx, 1);
      if (nk_button_label(ctx, "Translate")) {
        printf("%s\n", buf);
      }
      nk_spacing(ctx, 1);

      nk_layout_row(ctx, NK_DYNAMIC, 30, 3, tripleElementRatio);
      nk_label(ctx, "Output:", NK_TEXT_LEFT);
      nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, buf, sizeof(buf) - 1,
                                     nk_filter_default);
      nk_combobox(ctx, languages_names, languages.count, &currentToLang, 25,
                  nk_vec2(200, 200));
    }
    nk_end(ctx);

    /* Draw */
    glViewport(0, 0, win_width, win_height);
    glClear(GL_COLOR_BUFFER_BIT);
    nk_glfw3_render(&glfw, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER,
                    MAX_ELEMENT_BUFFER);
    glfwSwapBuffers(win);
  }
  nk_glfw3_shutdown(&glfw);
  glfwTerminate();
  return 0;
}
