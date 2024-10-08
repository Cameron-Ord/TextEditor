#ifndef MAIN_H
#define MAIN_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#define ASCII_CHAR_MIN 32
#define ASCII_CHAR_MAX 127

typedef struct {
  SDL_Window *w;
  SDL_Renderer *r;
  int width;
  int height;
} WindowData;

struct CharNode {
  unsigned char key;
  SDL_Texture *tex;
  SDL_Surface *surf;
  struct CharNode *next;
};

struct CharTable {
  struct CharNode *table[ASCII_CHAR_MAX];
};

typedef struct CharTable CharTable;
typedef struct CharNode CharNode;

typedef struct {
  char *character_buffer;
} Line;

typedef struct {
  Line *line_buffer;
} Editor;

extern WindowData win;

int scc(int code);
void *scp(void *ptr);
bool create_node(CharTable *hash_table_ptr, unsigned char key,
                 SDL_Surface *surf, SDL_Texture *tex);

#endif
