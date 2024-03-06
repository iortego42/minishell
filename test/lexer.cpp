#include "CppUTest/TestHarness.h"

extern "C" {
    #include "dfa.h"
}

TEST_GROUP(lexer_test)
{
};


TEST(lexer_test, basictest) {
    CHECK_EQUAL(1, 1);
}

