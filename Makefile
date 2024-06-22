NAME= minishell

CC = gcc
AR = ar
ARFLAGS = -rc
RM = rm -rf 
OBJSDIR = build
SRCDIR = src
INCDIR = include
CFLAGS = -Wall -Wextra -Werror -I./$(INCDIR)
LFTPATH = libft
LFTNAME = ft
LFT = $(LFTPATH)/lib$(LFTNAME).a
LSTRINGSPATH = libstrings
LSTRINGSNAME = strings
LSTRINGS = $(LSTRINGSPATH)/lib$(LSTRINGSNAME).a
CFLAGS += -I./$(LFTPATH)/include -I./$(LSTRINGSPATH)/include
# LDFLAGS += -lreadline
# LDFLAGS += -L $(LFTPATH) -l$(LFTNAME)
LDFLAGS += -L./$(LSTRINGSPATH) -l$(LSTRINGSNAME) 
# INFO: Tester sources
TESTPATH = test
UNITYPATH = $(TESTPATH)/unity
UNITYINC = $(UNITYPATH)/src
TESTSRCDIR = $(TESTPATH)/src
TESTBUILD = $(TESTPATH)/build
UNITYBUILD = $(UNITYPATH)/build

UNITYSRCS = unity.c
UNITYOBJS := $(addprefix $(TESTBUILD)/unity/,$(UNITYSRCS:%.c=%.o))
$(UNITYBUILD)/%.o: $(UNITYINC)/%.c | $(TESTBUILD)/unity
	$(CC) $(CFLAGS) -c $< -o $@ 
$(TESTBUILD)/unity: | $(TESTBUILD)
	mkdir $@

# INFO: lexer test sources
LEXERTESTSRCS = \
								 test_lexer.c
LEXERTESTOBJS := $(addprefix $(TESTBUILD)/lexer/,$(LEXERTESTSRCS:%.c=%.o))
$(TESTBUILD)/lexer/%.o: $(TESTSRCDIR)/lexer/%.c | $(TESTBUILD)/lexer
	$(CC) $(CFLAGS) -c $< -o $@ 
$(TESTBUILD)/lexer: | $(TESTBUILD)
	mkdir $@

SRCS = \
		minishell.c

LEXERDIR = $(SRCDIR)/lexer
LEXERSRCS = \
						actions.c \
						actions_2.c \
						actions_utils.c \
						clean.c \
						eval.c \
						lexer.c
LEXEROBJS := $(addprefix $(OBJSDIR)/lexer/,$(LEXERSRCS:%.c=%.o))
$(OBJSDIR)/lexer/%.o: $(LEXERDIR)/%.c | $(OBJSDIR)/lexer
	$(CC) $(CFLAGS) -c $< -o $@ 
$(OBJSDIR)/lexer: | $(OBJSDIR)
	mkdir $@


# OBJS := $(addprefix $(OBJSDIR)/,$(SRCS:%.c=%.o))

$(NAME): banner $(OBJS) $(LFT) $(LSTRINGS) banner
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@

all: $(NAME)

$(TESTBUILD):
	mkdir $@


lexertest: CFLAGS += -I $(UNITYINC)
lexertest: CFLAGS += -fsanitize=address -g3
lexertest: $(UNITYOBJS) $(LEXEROBJS) $(LEXERTESTOBJS) | $(TESTBUILD)/lexer $(LSTRINGS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(TESTBUILD)/$@

banner:
	@echo "\033[1;33m [!] WARNING [!]\033[0m\n\tWildcards are enabled\n\n"

$(LFT):
	make -C $(LFTPATH)

$(LSTRINGS):
	make -C $(LSTRINGSPATH)

$(OBJSDIR):
	mkdir build


clean:
	make fclean -C $(LFTPATH)
	make fclean -C $(LSTRINGSPATH)
	$(RM) $(OBJSDIR)

fclean: clean_mini
	$(RM) $(NAME)

re: fclean all

red: fclean debug_mini

res: fclean sanitize_mini

.PHONY: sanitize_mini debug_mini res red re clean_mini fclean all
