#include <stdio.h>

struct tape_symbol {
    struct tape_symbol *left;
    struct tape_symbol *right;
    char *symbol;
};

typedef enum {
    LEFT, RIGHT, STAY
} tape_dir;

void move_left();
void move_right();
char *read_symbol();
void write_symbol(char *symbol);
void rewind_tape();
void write_tape(FILE *fp);
