#include "CppUTest/TestHarness.h"
extern "C" {
    #include "libstrings.h"
    #include "dfa.h"
}

TEST_BASE(RedsTest)
{
    t_string    cmdstr;
    t_cmd       cmd;
    size_t      files;
    t_DFA       l;
    std::string sentence, testvalue, message;

    void setup() {
        l = (t_DFA){NULL,0,EMPTY_INPUT, EMPTY_INPUT, .cursor = NULL};
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
    t_string    e_cmdstr; 

    void setup() {
        RedsTest::setup();
        sentence = "Not reds getted with: ";
    } 

    void teardown() {
        ctor(&cmdstr, testvalue.c_str());
        message = sentence + testvalue;
        cmd = get_cmd(cmdstr, &l);
        // for (int i = 0; i < cmd->reds_c; printnl(cmd->reds[i++].filename));
        CHECK_TEXT(cmd->reds_c == files, message.c_str());
        CHECK_TEXT(str_cmp(e_cmdstr, cmd->cmd) == -1, message.c_str());
        dtor(&e_cmdstr);
        RedsTest::teardown();
    }
};

TEST(RedsCount, OneRedSQ)
{
    files = 1;
    ctor(&e_cmdstr, "echo OneRedSQ ");
    testvalue = "echo OneRedSQ >'esto'";
    // testvalue = "echo hola >'esto es una red'";
}

TEST(RedsCount, OneRedDQ)
{
    files = 1;
    ctor(&e_cmdstr, "echo OneRedDQ ");
    testvalue = "echo OneRedDQ >\"doubequotees\"";
}

TEST(RedsCount, TwoRedSimple)
{
    files = 2;
    ctor(&e_cmdstr, "echo TwoRedSimple  ");
    testvalue = "echo TwoRedSimple >>\"doubequotees\" >>EOF";
}

TEST(RedsCount, MultiRedsMix)
{
    files = 4;
    ctor(&e_cmdstr, "echo MultiRedsMix    ");
    testvalue = "echo MultiRedsMix >>\"append\" <infile <<heredoc >'hola'";
}

//
//  FILENAME TEST
//

TEST_GROUP_BASE(FilenameTest, RedsTest)
{
    t_string    *e_filename;
    char        **filenames;

    void setup() {
        RedsTest::setup();
        sentence = "Expected Values: ";
    };

    void copyFilenames(const char *filesn[]) {
        filenames = (char **)malloc(sizeof(char *) * (unsigned long)(files + 1));
        for (int i = 0; filesn[i]; i++) {
            filenames[i] = (char *)malloc(strlen(filesn[i]) + 1);
            strcpy(filenames[i], filesn[i]);
        }
        filenames[files] = NULL;
    };

    void teardown() {
        ctor(&cmdstr, testvalue.c_str());
        cmd = get_cmd(cmdstr, &l); 
        e_filename = (t_string *)malloc(sizeof(t_string) * (unsigned long)(files + 1));
        for (size_t i = 0; i < files; ctor(&e_filename[i], filenames[i]), i++);
        e_filename[files] = NULL;
        for (int i = 0; e_filename[i] != NULL; i++) {
            message = sentence + e_filename[i]->data + "\n" "Value obtained: " + cmd->reds[i].filename->data + "\n";
            CHECK_TEXT(str_cmp(e_filename[i], cmd->reds[i].filename) == -1, message.c_str());
        }
        for (int i = 0; e_filename[i] != NULL; dtor(&e_filename[i++]));
        free(e_filename);
        for (int i = 0; filenames[i]; free(filenames[i++]));
        free(filenames);
        RedsTest::teardown();
    };
};

TEST(FilenameTest, OneOutputNoQ)
{ 
    const char *filesn[] = {"hola", NULL};
    files = 1;
    testvalue = "echo OneOutputNoQ >hola";
    copyFilenames(filesn);
}

TEST(FilenameTest, Various)
{
    const char *filesn[] = {
        "outputfile",
        "'simpleheredoc'",
        "\"doubleappend\"",
        "\"doubleinput\"",
        "heredoc2",
        NULL
    };
    files = 5;
    testvalue = "echo Various >outputfile <<'simpleheredoc' >>\"doubleappend\" <\"doubleinput\" <<heredoc2";
    copyFilenames(filesn);
}

TEST(FilenameTest, SQWithWord)
{
    const char *filesn[] = {
        "'hola'hola",
        NULL
    };
    files = 1;
    testvalue = "echo SQWithWord > 'hola'hola ";
    copyFilenames(filesn);
}

TEST(FilenameTest, MixedQuotes)
{
    const char *filesn[] = {
        "\"hola\"hola'hola'\"'hola'\"",
        NULL
    };
    files = 1;
    testvalue = "echo MixedQuotes> \"hola\"hola'hola'\"'hola'\" ";
    copyFilenames(filesn);
}

TEST_GROUP_BASE(TypesTest, RedsTest)
{
    char        *e_type;


    void setup() {
        RedsTest::setup();
        sentence = "\nType expected: ";
    };
    void copyTypes(const char *types) {
        size_t length = strlen(types);

        e_type = (char *) malloc(length + 1);
        strcpy(e_type, types);
    };

    std::string typetostr(char type) {
        const char *TYPES[4] = {
            "INPUT",
	        "OUTPUT",
	        "APPEND",
	        "HEREDOC"
        };
        std::string res; 
        if (type & EXPAND)
        {
            type ^= EXPAND;
            res = "EXPAND - ";
        }
        res += TYPES[(int)type];
        return (res); 
    };
    void teardown() {
        ctor(&cmdstr, testvalue.c_str());
        cmd = get_cmd(cmdstr, &l); 
        for (int i = 0; e_type[i]; i++) {
            message = sentence + typetostr(e_type[i]) + "\n" "Value obtained: " + typetostr(cmd->reds[i].type) + "\n";
            CHECK_TEXT(e_type[i] == cmd->reds[i].type, message.c_str());
        }
        free(e_type);
        RedsTest::teardown();       
    };
};

TEST(TypesTest, ExpandInput)
{
    const char types[] = {
        INPUT | EXPAND,
        OUTPUT, 
        0
    };
    testvalue = "echo ExpandInput <$uno >\"dos\"";
    copyTypes(types);
}