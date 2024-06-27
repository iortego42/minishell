#ifndef TEST_LEXER_H
#define TEST_LEXER_H
#define UNITY_INCLUDE_CONFIG_H
#include "dfa.h"
#include <libstrings.h>
#include <unity.h>
#include <unity_internals.h>

t_string cmd;
t_string *pipes;
t_DFA l;

void base_count_pipes(const char *cmdstr, const int expected);
void test_count_pipes(void);
void test_tokens(void);
#endif
