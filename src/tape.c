#include "turing.h"
#include <stdlib.h>
#include <string.h>

struct tape_symbol *scanned_symbol = 0;

void move_left()
{
    if(scanned_symbol->left == 0)
    {
        scanned_symbol->left = (struct tape_symbol *)malloc(sizeof(struct tape_symbol));
        scanned_symbol->left->right = scanned_symbol;
        scanned_symbol->left->left = 0;
        scanned_symbol->left->symbol = "_";
    }
    scanned_symbol = scanned_symbol->left;
}

void move_right()
{
    if(scanned_symbol->right == 0)
    {
        scanned_symbol->right = (struct tape_symbol *)malloc(sizeof(struct tape_symbol));
        scanned_symbol->right->left = scanned_symbol;
        scanned_symbol->right->right = 0;
        scanned_symbol->right->symbol = "_";
    }
    scanned_symbol = scanned_symbol->right;
}

char *read_symbol()
{
    if(scanned_symbol == 0)
        return "_";
    return scanned_symbol->symbol;
}

void write_symbol(char *symbol)
{
    if(scanned_symbol == 0)
    {
        scanned_symbol = (struct tape_symbol *)malloc(sizeof(struct tape_symbol));
        scanned_symbol->left = 0;
        scanned_symbol->right = 0;
    }
    scanned_symbol->symbol = (char *)malloc(2);
    strcpy(scanned_symbol->symbol, symbol);
}

void rewind_tape()
{
    while(scanned_symbol->left != 0)
    {
        move_left();
    }
}

void write_tape(FILE *fp)
{
    rewind_tape();
    while(scanned_symbol->right != 0)
    {
        fprintf(fp, "%s ", read_symbol());
        move_right();
    }
}
