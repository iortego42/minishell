#define UNITY_CONFIG_H
#define UNITY_OUTPUT_COLOR
#define UNITY_INCLUDE_PRINT_FORMATTED
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define LIGHT_RED "\033[91m"
#define LIGHT_GREEN "\033[92m"
#define LIGHT_BLUE "\033[94m"
#define BOLD "\033[1m"
#define RESET "\033[0m"
#define RUN_TEST(testfunc)                                                     \
    UNITY_NEW_TEST(#testfunc)                                                  \
    printf(LIGHT_BLUE "  " RESET);                                          \
    if (TEST_PROTECT()) {                                                      \
        setUp();                                                               \
        testfunc();                                                            \
    }                                                                          \
    if (TEST_PROTECT() && (!TEST_IS_IGNORED))                                  \
        tearDown();                                                            \
    UnityConcludeTest();
