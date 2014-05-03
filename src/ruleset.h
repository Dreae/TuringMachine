typedef struct {
    tape_dir move_tape;
    char *target_state;
    char *write_symbol;
} rule;

struct symbol_node {
    struct symbol_node *right;
    struct symbol_node *left;
    struct state_node *state_root;
    char *symbol;
};

struct state_node {
    struct state_node *right;
    struct state_node *left;
    char *state;
    rule *rule;
};

int add_rule(char *current_state, char *scanned_symbol, char *write_symbol, tape_dir move_tape, char *target_state);
int append_rule(struct state_node *state, struct state_node **node);
void process_symbol(char *symbol, int *halt, char **state);
