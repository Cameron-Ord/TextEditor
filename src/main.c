#include "main.h"
#include <errno.h>

#define DEFAULT_LINE_COUNT 1
#define DEFAULT_CHAR_BUFFER 256

#define DEFAULT_WIN_HEIGHT 400
#define DEFAULT_WIN_WIDTH 300

WindowData win;

int main(int argc, char **argv) {

  scc(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER));
  scc(TTF_Init());

  win.w = scp(SDL_CreateWindow("Text Editor", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, DEFAULT_WIN_WIDTH,
                               DEFAULT_WIN_HEIGHT, SDL_WINDOW_RESIZABLE));

  win.r = scp(SDL_CreateRenderer(
      win.w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

  Editor editor;
  editor.line_buffer = malloc(sizeof(Line) * DEFAULT_LINE_COUNT);
  if (!editor.line_buffer) {
    printf("Failed to allocate the line buffer! -> %s\n", strerror(errno));
    return -1;
  }

  CharTable *char_table = (CharTable *)malloc(sizeof(CharTable));
  if (char_table) {
    printf("Failed to allocate char table! -> %s\n", strerror(errno));
    free(editor.line_buffer);
    return -1;
  }

  // Initialize table with null values
  for (size_t i = 0; i < ASCII_CHAR_MAX; i++) {
    char_table->table[i] = NULL;
  }

  for (size_t i = ASCII_CHAR_MIN; i < ASCII_CHAR_MAX; i++) {
    create_node(char_table, (unsigned char)i, NULL, NULL);
  }

  int quit = false;
  const int ticks_per_frame = (1000.0 / 60);
  uint64_t frame_start;
  int frame_time;

  while (!quit) {
    frame_start = SDL_GetTicks64();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT: {
        quit = true;
        break;
      }
      case SDL_TEXTINPUT: {

        break;
      }
      }
    }
    frame_time = SDL_GetTicks64() - frame_start;
    if (ticks_per_frame > frame_time) {
      SDL_Delay(ticks_per_frame - frame_time);
    }
  }

  TTF_Quit();
  SDL_Quit();
  return 0;
}

void *scp(void *ptr) {
  if (!ptr) {
    printf("SDL ERROR -> %s\n", SDL_GetError());
    exit(1);
  }

  return ptr;
}

int scc(int code) {
  if (code < 0) {
    printf("SDL ERROR -> %s\n", SDL_GetError());
    exit(1);
  }

  return code;
}
