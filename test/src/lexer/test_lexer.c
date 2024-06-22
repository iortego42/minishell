#include "test_lexer.h"
#include "libstrings.h"

t_string cmd;
t_string *pipes;
t_DFA l;
const char *cmdstr;

void setUp(void) {
    ctor(&cmd, cmdstr);
    l = (t_DFA){.pipes_pos = NULL,
                .pipes_c = 0,
                .cursor = str_cpy(cmd),
                .state = EMPTY_INPUT,
                .prev_state = EMPTY_INPUT};
    init_trans(&l);
}
void tearDown(void) { clearlist(&pipes); }

void test_count_pipes(void) {
    int counter, expected = 2;
    pipes = get_pipe_list(&l);
    for (counter = 0; pipes[counter] != NULL; counter++, counter++) {
        print(pipes[counter]);
    }
    TEST_ASSERT_EQUAL(expected, counter);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_count_pipes);
    return (0);
}
