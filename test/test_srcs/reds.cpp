#include "CppUTest/TestHarness.h"
extern "C" {
    #include "libstrings.h"
    #include "dfa.h"
}

TEST_BASE(RedsTest)
{
    t_string    cmdstr;
    t_cmd       cmd;
    std::string sentence, testvalue, message;
    
    void setup() {
        cmdstr = NULL;
    };
    void teardown() {
        if (cmdstr)
            dtor(&cmdstr);
        if (cmd) 
            clean_cmd(&cmd);
    };
};

//
//  SAME REDS NUMBER TESTS
//

TEST_GROUP_BASE(RedsCount, RedsTest)
{
    int         expected_reds;
    t_string    expected_cmdstr; 

    void setup() {
        RedsTest::setup();
        sentence = "Not reds getted with: ";
    } 

    void teardown() {
        ctor(&cmdstr, testvalue.c_str());
        message = sentence + testvalue;
        cmd = get_cmd(cmdstr);
        for (int i = 0; i < cmd->reds_c; printnl(cmd->reds[i++].filename));
        printnl(cmd->cmd);
        CHECK_TEXT(cmd->reds_c == expected_reds, message.c_str());
        CHECK_TEXT(str_cmp(expected_cmdstr, cmd->cmd) == -1, message.c_str());
        dtor(&expected_cmdstr);
        RedsTest::teardown();
    }
};

TEST(RedsCount, OneRedSC)
{
    expected_reds = 1;
    ctor(&expected_cmdstr, "echo OneRedSC ");
    testvalue = "echo OneRedSC >'esto'";
    // testvalue = "echo hola >'esto es una red'";
}

TEST(RedsCount, OneRedDC)
{
    expected_reds = 1;
    ctor(&expected_cmdstr, "echo OneRedDC ");
    testvalue = "echo OneRedDC >\"doubequotees\"";
}

TEST(RedsCount, TwoRedSimple)
{
    expected_reds = 2;
    ctor(&expected_cmdstr, "echo TwoRedSimple  ");
    testvalue = "echo TwoRedSimple >>\"doubequotees\" >>EOF";
}

TEST(RedsCount, MultiRedsMix)
{
    expected_reds = 4;
    ctor(&expected_cmdstr, "echo MultiRedsMix    ");
    testvalue = "echo MultiRedsMix >>\"append\" <infile <<heredoc >'hola'";
}