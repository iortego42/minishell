# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iortego- <iortego-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/25 18:43:24 by iortego-          #+#    #+#              #
#    Updated: 2023/11/04 12:45:36 by iortego-         ###   ########.fr        #
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


LDFLAGS += -L $(LFTPATH) -l$(LFTNAME),readline
CFLAGS = -I $(INCDIR)
LFTPATH = libft
LFTNAME = ft
LFT = $(LFTPATH)/lib$(LFTNAME).a
CFLAGS += -I $(LFTPATH)/include

SRCS = minishell.c

SRCS += \
		builtins/echo.c \
		builtins/exit.c \
		builtins/pwd.c \
		builtins/env.c

SRCS += \
		utils/ft_calloc.c \
		utils/ft_strequals.c \
		utils/ft_strjoin.c \
		utils/ft_strlen.c \
		utils/ft_substrchr.c \
		utils/ft_strstartswith.c

SRCS += \
		parser/parser_main.c \
		parser/lexer.c

OBJS := $(addprefix $(OBJDIR)/,$(SRCS:%.c=%.o))

all: $(NAME)

sanitize: CFLAGS += -fsanitize=address -g3 
sanitize: $(OBJS) $(LFTNAME)sanitize
	@echo "[$(NAME)]->>\033[34m [◊] SANITIZE MODE ON [◊]\033[0m"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) 

debug: CFLAGS += -g3
debug: $(OBJS) $(LFTNAME)debug
	@echo "[$(NAME)]->>\033[33m [∆] DEBUG MODE ON [∆]\033[0m"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)  

$(NAME): $(OBJS) $(LFT)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(LFTNAME)debug:
	make -C $(LFTPATH) debug

$(LFTNAME)sanitize:
	make -C $(LFTPATH) sanitize

$(LFT): 
	make -C $(LFTPATH)	

$(OBJDIR): 
	mkdir $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	make fclean -C $(LFTPATH)
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

red: fclean debug

res: fclean sanitize

.PHONY: sanitize debug res red re clean fclean all
