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
        TEST_ASSERT_EQUAL_STRING(cmds[i], (*list)->str->data);
    l.cmd_p->cmd = NULL;
    l.cmd_p->reds = NULL;
}

void test_simple(void) {
    const char *tokens[] = {"echo", "hello", NULL};
    const char cmdstr[] = "echo hello";
    base_test(cmdstr, tokens);
}

void test_word_sq(void) {
    const char *tokens[] = {"echo", "fuera", "dentro", NULL};
    const char cmdstr[] = "echo fuera'dentro'";
    base_test(cmdstr, tokens);
}

void test_sq_word(void) {
    const char *tokens[] = {"ls", "dentro", "fuera", NULL};
    const char cmdstr[] = "ls 'dentro'fuera";
    base_test(cmdstr, tokens);
}

void test_dq_word(void) {
    const char *tokens[] = {"ls", "ruta   con  espacios/", "archivo", NULL};
    const char cmdstr[] = "ls \"ruta   con  espacios/\"archivo";
    base_test(cmdstr, tokens);
}

void test_dq_word_sq(void) {
    const char *tokens[] = {"ping", "-c", "1", "1.", "1.1", ".1", NULL};
    const char cmdstr[] = "ping -c 1 \"1.\"1.1'.1'";
    base_test(cmdstr, tokens);
}

void test_empty_dq() {
    const char *tokens[] = {"whoami", NULL};
    const char cmdstr[] = "whoami \"\"";
    base_test(cmdstr, tokens);
}

void test_variable() {
    const char *tokens[] = {"echo", "$hola", NULL};
    const char cmdstr[] = "echo $hola";
    base_test(cmdstr, tokens);
}

void test_dq_variable() {
    const char *tokens[] = {"echo", "$hola", "' $mundo", NULL};
    const char cmdstr[] = "echo $hola\"' $mundo\"  ";
    base_test(cmdstr, tokens);
}
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_simple);
    RUN_TEST(test_word_sq);
    RUN_TEST(test_sq_word);
    RUN_TEST(test_dq_word);
    RUN_TEST(test_dq_word_sq);
    RUN_TEST(test_empty_dq);
    RUN_TEST(test_variable);
    RUN_TEST(test_dq_variable);
    return (0);
}
