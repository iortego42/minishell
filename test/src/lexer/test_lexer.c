#include "test_lexer.h"

t_string cmd;
t_string *pipes;
t_DFA l;

void setUp(void) {
    l = (t_DFA){.pipes_pos = NULL,
                .pipes_c = 0,
                .state = EMPTY_INPUT,
                .prev_state = EMPTY_INPUT};
    init_trans(&l);
}

void tearDown(void) {
    clearlist(&pipes);
    dtor(&cmd);
}

void base_count_pipes(const char *cmdstr, const int expected) {
    int counter;

    ctor(&cmd, cmdstr);
    l.cursor = str_cpy(cmd);
    pipes = get_pipe_list(&l);
    for (counter = 0; pipes[counter] != NULL; counter++) {
        print(pipes[counter]);
    }
    TEST_ASSERT_EQUAL_MESSAGE(expected, counter, "test");
}
void test_count_pipes(void) { base_count_pipes("echo hello | world", 2); }

void test_count_pipes_s(void) { base_count_pipes("echo hola", 2); }

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_count_pipes);
    RUN_TEST(test_count_pipes_s);
    return (0);
}
