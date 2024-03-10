# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nachh <nachh@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/25 18:43:24 by iortego-          #+#    #+#              #
#    Updated: 2024/03/10 17:16:03 by nachh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell

CC = gcc
AR = ar
ARFLAGS = -rc
RM = rm -rf 
OBJDIR = build
SRCDIR = src
INCDIR = include

CFLAGS = -Wall -Wextra -Werror -I $(INCDIR)
LFTPATH = libft
LFTNAME = ft
LFT = $(LFTPATH)/lib$(LFTNAME).a
LSTRINGSPATH = libstrings
LSTRINGSNAME = strings
LSTRINGS = $(LSTRINGSPATH)/lib$(LSTRINGSNAME).a
CFLAGS += -I $(LFTPATH)/include -I $(LSTRINGSPATH)/include
LDFLAGS += -lreadline -L $(LFTPATH) -l$(LFTNAME) -L $(LSTRINGSPATH) -l$(LSTRINGSNAME) 

SRCS = \
		minishell.c \
		env.c

SRCS += \
		builtins/builtins.c \
		builtins/echo.c \
		builtins/env.c \
		builtins/exit.c \
		builtins/pwd.c

# SRCS += \
# 		parser/lexer.c

SRCS += parser/*.c

OBJS := $(addprefix $(OBJDIR)/,$(SRCS:%.c=%.o))

all: $(NAME)

sanitize_mini: CFLAGS += -fsanitize=address -g3
sanitize_mini: $(OBJS) $(LFTNAME)sanitize $(LSTRINGS)sanitize banner
	@echo "[$(NAME)]->>\033[34m [◊] SANITIZE MODE ON [◊]\033[0m"
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)

debug_mini: CFLAGS += -g3
debug_mini: $(OBJS) $(LFTNAME)debug $(LSTRINGS)debug banner
	@echo "[$(NAME)]->>\033[33m [∆] DEBUG MODE ON [∆]\033[0m"
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)

banner:
	@echo "\033[1;33m [!] WARNING [!]\033[0m\n\tWildcards are enabled\n\n\n"
$(NAME): banner $(OBJS) $(LFT) $(LSTRINGS) banner
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@

$(LFTNAME)debug:
	make -C $(LFTPATH) debug

$(LFTNAME)sanitize:
	make -C $(LFTPATH) sanitize

$(LFT):
	make -C $(LFTPATH)

$(LSTRINGSNAME)debug:
	make -C $(LSTRINGSPATH) libdebug

$(LSTRINGSNAME)sanitize:
	make -C $(LSTRINGSPATH) sanitize

$(LSTRINGS):
	make -C $(LSTRINGSPATH)

$(OBJDIR):
	mkdir build
	mkdir build/builtins
	mkdir build/parser

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ 

# ------------------------- Test Rules -------------------------
# Use the variable FILE to specify a file to test
# Example file relative path is src/parsers/lexer.c:
# 	$ make test FILE=parser/lexer.c
#


#
#	---{[############}-CPPUTEST-{############]}---
#
COMPONENT_NAME=minishell
# GENERAL ROUTES
MAKEFILE_DIR=.
PROJECT_DIR=.
TEST_DIR=test
CPPUTEST_HOME=$(TEST_DIR)/cpputest
CPPUTEST_PEDANTIC_ERRORS=N
# CPPUTEST BUILDS ROUTES
CPPUTEST_OBJS_DIR=$(TEST_DIR)/objs
CPPUTEST_LIB_DIR=$(TEST_DIR)/lib
# CPPUTEST FLAGS
CPPFLAGS += -I$(CPPUTEST_HOME)/include
# CPPUTEST LINKING FLAG
LD_LIBRARIES = -L$(CPPUTEST_HOME)/lib -lCppUTest
# PROJECT SOURCES DIR
# SRC_DIRS=$(PROJECT_DIR)/src
SRC_DIRS+=$(PROJECT_DIR)/libstrings/src
SRC_FILES=$(PROJECT_DIR)/src/parser/lexer.c
# COMPILING INCLUDE FLAGS
INCLUDE_DIRS=$(PROJECT_DIR)/include
INCLUDE_DIRS+=$(PROJECT_DIR)/libstrings/include
INCLUDE_DIRS+=$(PROJECT_DIR)/libft/include
INCLUDE_DIRS+=$(CPPUTEST_HOME)/include
# TEST SOURCES DIR
TEST_SRC_DIRS=$(TEST_DIR)/test_srcs
# ADDRESS SANITIZATION
CXXFLAGS += -fsanitize=address
CFLAGS += -fsanitize=address
# CPPUTEST_CXXFLAGS += -fsanitize=address
# CPPUTEST_CFLAGS += -fsanitize=address
# MEMORY LEAK DETECTION
CPPUTEST_USE_MEM_LEAK_DETECTION=Y
CXXFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h
CPPUTEST_CXXFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
CPPUTEST_CFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h
# CPPUTEST DEFAULT MAKEFILE INCLUSION
include $(CPPUTEST_HOME)/build/MakefileWorker.mk
#
#	---{[############}-RULES-{#############]}-----
#
unitest: $(TEST_TARGET) 
	./$(TEST_TARGET) -c

reunitest: clean clean_mini unitest

#
# 	---{[####################################]}---
#


#
# --------------------------------------------------------------
#

clean_mini:
	make fclean -C $(LFTPATH)
	make fclean -C $(LSTRINGSPATH)
	$(RM) $(OBJDIR)

fclean: clean_mini
	$(RM) $(NAME)

re: fclean all

red: fclean debug_mini

res: fclean sanitize_mini

.PHONY: sanitize_mini debug_mini res red re clean_mini fclean all
