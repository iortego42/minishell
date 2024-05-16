#include "CppUTest/TestHarness.h"
extern "C" {
    #include "libstrings.h"
    #include "dfa.h"
}

TEST_BASE(LexerTest)
{
    t_string        command;
    t_cmd        *pipe_list;
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
        {
            char a = g_alphabets[0][0];
            a = '\0';
            printf("%c", a);
            clean_cmd_list(&pipe_list);
            pipe_list = NULL;
        }
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
        // p_printlist(pipe_list, (char *)"\n->");
        CHECK_TEXT(NULL != pipe_list, message.c_str());
        LexerTest::teardown();
    }
};

TEST_GROUP_BASE(InvalidCommand, LexerTest)
{
    void setup()
    {
        LexerTest::setup();
        sentence = "Invalid command lexed: ";
    }
    void teardown()
    {
        // printf("\nTesting: %s\n", testvalue.c_str());
        ctor(&command, testvalue.c_str());
        message = sentence + testvalue;
        pipe_list = lexer(command);
        // p_printlist(pipe_list, (char *)"\n->");
        CHECK_TEXT(NULL == pipe_list, message.c_str());
        LexerTest::teardown();
    }
};

TEST_GROUP_BASE(NumberOfPipes, LexerTest)
{
    int expected_pipes;
    void setup()
    {
        LexerTest::setup();
        sentence = "Invalid number of pipes: ";
    }   
    void teardown()
    {
        int obtained_pipes = 0;
        //printf("\nNumber: ", )
        ctor(&command, testvalue.c_str());
        pipe_list = lexer(command);
        if (pipe_list)
            for (obtained_pipes = -1; pipe_list[obtained_pipes + 1] != NULL; obtained_pipes++);
        message = sentence + testvalue + "\nObtained: " + std::to_string(obtained_pipes)
                                       + "\nExpected: " + std::to_string(expected_pipes);
        // p_printlist(pipe_list, (char *)"<->");
        LexerTest::teardown();
        CHECK_TEXT(expected_pipes == obtained_pipes, message.c_str());
    }
};

//
//  VALID COMMANDS TESTS
//
TEST(ValidCommand, simpleCommand)
{
    testvalue = "echo hola";
}

TEST(ValidCommand, onePipe)
{
    testvalue = "ls | wc";
}

TEST(ValidCommand, pipeWithRed)
{
    testvalue = "ls >file1 /route/to/list >>file3 <<EOF";
}
//
//  INVALID COMMANDS TESTS
//
TEST(InvalidCommand, pipeAtBegin)
{
    testvalue = "| exit";
}

TEST(InvalidCommand, pipeWithEmptyRedir)
{
    testvalue = "exit | exit >";
}

//
// PIPE NUMBER ON VALID COMMANDS TESTS
//
TEST(NumberOfPipes, noPipe)
{
    testvalue = "echo \"sin pipe\"";
    expected_pipes = 0;
}

TEST(NumberOfPipes, onePipe)
{
    testvalue = "echo | ls -la";
    expected_pipes = 1;
}

TEST(NumberOfPipes, pipeInsideString)
{
    testvalue = "echo \"hola | que tal\"";
    expected_pipes = 0;
}
TEST(NumberOfPipes, twoPipes)
{
    testvalue = "echo \"Hola que tal\" | ls | cat";
    expected_pipes = 2;
}

TEST(NumberOfPipes, test)
{
    testvalue = "echo '''''|'''";
    expected_pipes = 0;
}