# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nachh <nachh@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/25 18:43:24 by iortego-          #+#    #+#              #
#    Updated: 2024/03/06 06:58:29 by nachh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell

CC  = gcc
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


CPPUTEST_HOME = test/cpputest

SRCS = minishell.c

# SRCS += \
# 		builtins/echo.c \
# 		builtins/exit.c \
# 		builtins/pwd.c \
# 		builtins/env.c

# SRCS += \
# 		parser/lexer.c

SRCS += parser/*.c builtins/*.c AST/*.c

OBJS := $(addprefix $(OBJDIR)/,$(SRCS:%.c=%.o))

all: $(NAME)

sanitize: CFLAGS += -fsanitize=address -g3
sanitize: $(OBJS) $(LFTNAME)sanitize $(LSTRINGS)sanitize banner
	@echo "[$(NAME)]->>\033[34m [◊] SANITIZE MODE ON [◊]\033[0m"
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)

debug: CFLAGS += -g3
debug: $(OBJS) $(LFTNAME)debug $(LSTRINGS)debug banner
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
	make -C $(LSTRINGSPATH) debug

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

# ---- Test Rules ----
# Use the variable FILE to specify a file to test
# Example file relative path is src/parsers/lexer.c:
# 	$ make test FILE=parser/lexer.c
#

test:
	make -f

clean:
	make fclean -C $(LFTPATH)
	make fclean -C $(LSTRINGSPATH)
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

red: fclean debug

res: fclean sanitize

.PHONY: sanitize debug res red re clean fclean all
