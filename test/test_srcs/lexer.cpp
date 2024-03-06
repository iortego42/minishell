#include "CppUTest/TestHarness.h"

extern "C" {
    #include "dfa.h"
}

TEST_GROUP(lexer_test)
{
};


TEST(lexer_test, init) {
    CHECK_EQUAL(1, 1);
}

TEST(lexer_test, checkSimple)
{
    t_string test;
    ctor(&test, (char*)"hola hola");
    CHECK_TEXT(NULL != lexer(test), "Valid command");

    
}

