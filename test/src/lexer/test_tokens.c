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
    clean_cmd(&command);
}

void base_test(const char cmdstr[], const char *cmds[]) {
    t_token *list;
    ctor(&cmd, cmdstr);
    l.cursor = str_cpy(cmd);
    get_tokens_list(&l);
    list = l.cmd_p->tokens;
    while ((*list)->left != NULL)
        (*list) = (*list)->left;

    for (int i = 0; (*list) != NULL && cmds[i] != NULL;
         i++, (*list) = (*list)->right)
        TEST_ASSERT_EQUAL_STRING((*list)->str->data, cmds[i]);
    l.cmd_p->cmd = NULL;
    l.cmd_p->reds = NULL;
}

void test_tokens(void) {
    base_test("echo hello'hola'",
              (const char *[]){"echo", "hello", "'hola'", NULL});
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_tokens);
    return (0);
}
