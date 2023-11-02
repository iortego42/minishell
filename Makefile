# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danimart <danimart@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/25 18:43:24 by iortego-          #+#    #+#              #
#    Updated: 2023/11/02 04:53:13 by danimart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell

CC = gcc
RM = rm -rf
OBJDIR = build
SRCDIR = src

CFLAGS = -Wall -Wextra -Werror -I include

SRCS = minishell.c

SRCS += builtins/echo.c

SRCS += utils/ft_strlen.c utils/startswith.c

OBJS := $(addprefix $(OBJDIR)/,$(SRCS:%.c=%.o))

all: $(NAME)

sanitize: CFLAGS += -fsanitize=address -g3
sanitize: $(OBJS) $(LFTNAME)sanitize
	@echo "[$(NAME)]->>\033[34m [◊] SANITIZE MODE ON [◊]\033[0m"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

debug: CFLAGS += -g3
debug: $(OBJS)
	@echo "[$(NAME)]->>\033[33m [∆] DEBUG MODE ON [∆]\033[0m"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -lreadline $(OBJS) -o $(NAME)

$(OBJDIR):
	mkdir build
	mkdir build/builtins
	mkdir build/utils

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

red: fclean debug

res: fclean sanitize

.PHONY: sanitize debug res red re clean fclean all
