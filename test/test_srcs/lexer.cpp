#include "CppUTest/TestHarness.h"
extern "C" {
    #include "libstrings.h"
    #include "dfa.h"
}

TEST_BASE(LexerTest)
{
    t_string        command;
    t_string        *pipe_list;
    std::string     sentence, testvalue, message;

    void setup()
    {
        command = NULL;
        pipe_list = NULL;
    }

    void teardown()
    {
        if (command) 
            dtor(&command);
        if (pipe_list) 
            clearlist(pipe_list);
    }
};

TEST_GROUP_BASE(ValidCommand, LexerTest)
{
    void setup()
    {
        LexerTest::setup();
        sentence = "Valid command not lexed: ";
    }
    void teardown()
    {
        // printf("\nTesting: %s\n", testvalue.c_str());
        ctor(&command, testvalue.c_str());
        message = sentence + testvalue;
        pipe_list = lexer(command);
        CHECK_TEXT(NULL != pipe_list, message.c_str());
        LexerTest::teardown();

    }
};

TEST(ValidCommand, simpleCommand)
{
    testvalue = "hola hola";
}

TEST(ValidCommand, onePipe)
{
    testvalue = "hola | hola";
}

TEST(ValidCommand, pipeWithRed)
{
    testvalue = "hola >file1 file2 >>file3 <<EOF";
}
