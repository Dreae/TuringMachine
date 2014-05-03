#include <stdlib.h>
#include "turing.h"

int run()
{
    char *state = "0";
    int halt = 0;
    int steps = 0;
    while(!halt)
    {
        char *symbol = read_symbol();
        process_symbol(symbol, &halt, &state);
        steps++;
    }

    printf("Completed\nSteps: %i\n", steps);
    printf("Attempting to write output to file...\n");
    FILE *fp = fopen("out.tape", "w");
    if(fp != NULL)
    {
        write_tape(fp);
        fclose(fp);
        printf("Wrote tape to out.tape\n");
    }
    else
    {
        printf("Failed to open output file\n");
    }
    return 0;
}
