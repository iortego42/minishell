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
UNITYBUILD = $(TESTBUILD)/unity

# INFO: Ruta del unity_config.h
CFLAGS += -I./$(TESTSRCDIR)

CFLAGS += -I $(UNITYINC)        
CFLAGS += -g3

# INFO: Archivos Unity
UNITYSRCS = unity.c
UNITYOBJS := $(addprefix $(UNITYBUILD)/,$(UNITYSRCS:%.c=%.o))
$(UNITYBUILD)/%.o: $(UNITYINC)/%.c | $(UNITYBUILD)
	$(CC) $(CFLAGS) -c $< -o $@  -DUNITY_INCLUDE_CONFIG_H
$(UNITYBUILD): | $(TESTBUILD)
	mkdir $@

# INFO: lexer test sources
LEXERTESTSRCS = \
								 test_tokens.c \
								 test_pipes.c
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
						token.c \
						lexer.c
LEXEROBJS := $(addprefix $(OBJSDIR)/lexer/,$(LEXERSRCS:%.c=%.o))
$(OBJSDIR)/lexer/%.o: $(LEXERDIR)/%.c | $(OBJSDIR)/lexer
	$(CC) $(CFLAGS) -c $< -o $@ 
$(OBJSDIR)/lexer: | $(OBJSDIR)
	mkdir $@


# OBJS := $(addptefix $(OBJSDIR)/,$(SRCS:%.c=%.o))

$(NAME): banner $(OBJS) $(LFT) $(LSTRINGS) banner
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@

all: $(NAME)

$(TESTBUILD):
	mkdir $@

# INFO: Regla para compilar los distintos binarios para los tests
TESTBINS := $(addprefix $(TESTBUILD)/,$(LEXERTESTSRCS:%.c=%))
# CFLAGS += -fsanitize=address 
$(TESTBUILD)/%: $(TESTBUILD)/lexer/%.o $(UNITYOBJS) $(LEXEROBJS) | $(TESTBUILD) $(LSTRINGS)
	@echo " \033[32;1m⬣\033[0m Compilando:" $@
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

test_binaries: $(TESTBINS)

test:  test_binaries
	@for executable in $(TESTBUILD)/test_*; do \
		echo ; \
		for i in {1..60}; do \
			/bin/echo -n '–'; \
		done; echo; \
		echo  "[\033[94mTESTS\033[0m]\t\t$$executable" ;\
		for i in {1..60}; do \
			/bin/echo -n '–'; \
		done; echo; \
		$$executable ;\
	done

retest: clean_test test

$(LFT):
	make -C $(LFTPATH)

$(LSTRINGS):
	make -C $(LSTRINGSPATH)

$(OBJSDIR):
	mkdir build

clean_test: fclean
	$(RM) $(TESTBUILD) $(UNITYBUILD)

clean:
	make fclean -C $(LFTPATH)
	make fclean -C $(LSTRINGSPATH)
	$(RM) $(OBJSDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: retest test_binaries test clean_test fclean re all
.PRECIOUS: $(TESTBUILD)/%.o $(UNITYBUILD)/%.o $(TESTBUILD)/lexer/%.o $(OBJSDIR)/lexer/%.o
