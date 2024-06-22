#include "test_tokens.h"
#include "libstrings.h"
#include "unity.h"
#include "unity_internals.h"
#include <stdio.h>

void setUp(void) {}

void tearDown(void) { system("leaks test_tokens"); }

void test_tokens(void) {}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST_AT_LINE(test_tokens, __LINE__);
    return (0);
}
