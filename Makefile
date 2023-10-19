# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danimart <danimart@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/19 04:09:11 by danimart          #+#    #+#              #
#    Updated: 2023/10/19 04:13:53 by danimart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
CC=gcc

C_FILES=minishell.c
C_FLAGS=-Wall -Werror -Wextra

O_FILES=$(C_FILES:.c=.o)

all: $(NAME)
$(NAME): $(O_FILES)
	@printf "\n\e[0;33m-\e[1;32m "
	$(CC) $(C_FLAGS) $(O_FILES) -o $(NAME)
	@printf "\n\033[0m"
clean:
	@printf "\n\e[0;33m-\e[1;32m "
	rm -rf $(O_FILES)
	@printf "\n\033[0m"
fclean:
	@printf "\n\e[0;33m-\e[1;32m "
	rm -rf $(NAME) $(O_FILES)
	@printf "\n\033[0m"
re: fclean $(NAME)
.PHONY: all clean fclean re
