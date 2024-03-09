#include "CppUTest/TestHarness.h"

extern "C" {
    #include "libstrings.h"
}

TEST_GROUP(lexer_test)
{
};


TEST(lexer_test, init) {
    CHECK_EQUAL(1, 1);
}

TEST(lexer_test, checkSimple)
{
    t_string test, cpy;
    ctor(&test, (char*)"hola hola");
    cpy = str_cpy(test);
    CHECK_COMPARE_TEXT(test->data_len, ==, cpy->data_len, "Checking data_lenght");
    CHECK_TEXT(-1 == str_cmp(test, cpy), "Checking data with str_cmp");
    dtor(&test);
    dtor(&cpy);
    
}

