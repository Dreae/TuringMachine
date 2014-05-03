#include "turing.h"
#include <stdlib.h>
#include <string.h>

struct state_node **symbols = 0;

int add_rule(char *current_state, char *scanned_symbol, char *write_symbol, tape_dir move_tape, char *target_state)
{
    if(symbols == 0)
        symbols = (struct state_node **)calloc(255, sizeof(struct state_node));
    struct state_node *state = (struct state_node *)malloc(sizeof(struct state_node));
    state->left = 0;
    state->right = 0;
    state->state = malloc(strlen(current_state));
    strcpy(state->state, current_state);
    
    state->rule = malloc(sizeof(rule));
    state->rule->move_tape = move_tape;
    
    state->rule->target_state = malloc(strlen(target_state));
    strcpy(state->rule->target_state, target_state);
    state->rule->write_symbol = malloc(strlen(write_symbol));
    strcpy(state->rule->write_symbol, write_symbol);
    
    if(symbols[(int)scanned_symbol[0]] == 0)
    {
        symbols[(int)scanned_symbol[0]] = state;
        return 0;
    }
    else
    {
        return append_rule(state, &symbols[(int)scanned_symbol[0]]);
    }
}

int append_rule(struct state_node *state, struct state_node **node)
{ 
    while(1)
    {
        if(*node == 0)
        {
            *node = state;
            return 0;
        }
        else if(strcmp(state->state, (*node)->state) == 0)
        {
            fprintf(stderr, "ERROR: Duplicate rule! Machine must be deterministic\n");
            return 1;
        }
        else if(strcmp(state->state, (*node)->state) < 0)
        {
            node = &(*node)->left;
            continue;
        }
        else if(strcmp(state->state, (*node)->state) > 0)
        {
            node = &(*node)->right;
            continue;
        }
        break;
    }
    return 1;
}
        
struct state_node *find_symbol_node(char *symbol)
{
    if(symbols[(int)symbol[0]] == 0)
    {
        fprintf(stderr, "ERROR: No rule for current symbol and state\n");
        return 0;
    }
    return symbols[(int)symbol[0]];
}
        
struct state_node *find_state_node(struct state_node **node, char *state)
{
    while(1)
    {
        if(*node == 0)
        {
            fprintf(stderr, "ERROR: No rule for current symbol and state\n");
            return 0;
        }
        else if(strcmp(state, (*node)->state) == 0)
        {
            return *node;
        }
        else if(strcmp(state, (*node)->state) < 0)
        {
            node = &(*node)->left;
            continue;
        }
        else if(strcmp(state, (*node)->state) > 0)
        {
            node = &(*node)->right;
            continue;
        }
        break;
    }
    return 0;
}
    
    
void process_symbol(char *symbol, int *halt, char **state)
{
    struct state_node *node = find_symbol_node(symbol);
    struct state_node *snode = find_state_node(&node, *state);
    if(node == 0 || snode == 0)
    {
        fprintf(stderr, "State: %s\nSymbol: %s\n", *state, symbol);
        *halt = 1;
        return;
    }
    write_symbol(snode->rule->write_symbol);
    if(snode->rule->move_tape == RIGHT)
        move_right();
    else if(snode->rule->move_tape == LEFT)
        move_left();
    *state = snode->rule->target_state;
    if(strcmp(*state, "halt") == 0)
        *halt = 1;
}
