#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "turing.h"

int scan_ruleset(char *file);
int scan_input(char *file);
int parse_arguments(int argc, char **argv);


int parse_arguments(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("Usage: turing {rule file} [ {input tape} ]\n");
        return 1;
    }
    if(argc > 2)
    {
        return scan_ruleset(argv[1]) + scan_input(argv[2]);
    }

    return scan_ruleset(argv[1]);
}

int scan_ruleset(char *file)
{
    FILE *rules = fopen(file, "r");
    if(rules == NULL)
    {
        printf("Error opening ruleset file\n");
        return 1;
    }
    char cstate[64];
    char ssymbol[2];
    char wsymbol[2];
    char move[2];
    char tstate[64];
    while(fscanf(rules, "%s %s %s %s %s", cstate, ssymbol, wsymbol, move, tstate) > 0)
    {
        if(strcmp(move, "R") == 0 || strcmp(move, "r") == 0)
            add_rule(cstate, ssymbol, wsymbol, RIGHT, tstate);
        else if(strcmp(move, "L") == 0 || strcmp(move, "l") == 0)
            add_rule(cstate, ssymbol, wsymbol, LEFT, tstate);
        else
            add_rule(cstate, ssymbol, wsymbol, STAY, tstate);
    }
    fclose(rules);
    return 0;
}

int scan_input(char *file)
{
    FILE *input = fopen(file, "r");
    if(input == NULL)
    {
        printf("Error opening input file\n");
        return 1;
    }

    char line[255];
    char *symbol = (char *)malloc(1);
    int c;

    while(fgets(line, sizeof(line), input) != NULL)
    {
        for(c = 0; c < strlen(line); c++)
        {
            if(!isspace(line[c]))
            {
		*symbol = line[c];
                write_symbol(symbol);
                move_right();
            }
        }
    }
    rewind_tape();
    fclose(input);
    return 0;
}

int main(int argc, char **argv)
{
    if(parse_arguments(argc, argv) > 0)
    {
        printf("Error parsing command line arguments\n");
        return 1;
    }
    return run();
}
