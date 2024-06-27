#include "test_lexer.h"

t_cmd command;

void setUp(void) {
    command = malloc(sizeof(struct s_cmd));
    l = (t_DFA){.pipes_pos = NULL,
                .pipes_c = 0,
                .state = EMPTY_INPUT,
                .cmd_p = command,
                .prev_state = EMPTY_INPUT};
    init_trans(&l);
}

void tearDown(void) {
    dtor(&cmd);
    clean_cmd(&l.cmd_p);
}

void test_tokens(void) {
    const char *cmdstr;
    ctor(&cmd, cmdstr);
    l.cursor = cmd;
    // get_cmd(cmd, &l);
    get_tokens_list(&l);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_tokens);
    return (0);
}
