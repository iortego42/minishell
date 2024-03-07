NAME= libft.a

CC = gcc
AR = ar
ARFLAGS = -rc
RM = rm -rf 
OBJDIR = build
SRCDIR = src
INCDIR = include


# CFLAGS = -Wall -Wextra -Werror  -I $(INCDIR) -fsanitize=address
CFLAGS = -Wall -Wextra -Werror -I $(INCDIR)

SRCS =	\
		ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_how_many_char.c \
		ft_how_many_word.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_isspace.c \
		ft_itoa.c \
		ft_lstadd_back_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstfirst.c \
		ft_lstiter_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstmap_bonus.c \
		ft_lstnew_bonus.c \
		ft_lstsize_bonus.c \
		ft_matrix_delete.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memchr.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strchrindex.c \
		ft_strdup.c \
		ft_strequals.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strtrim.c \
		ft_strrchr.c \
		ft_strstartswith.c \
		ft_substr.c \
		ft_substrchr.c \
		ft_switch.c \
		ft_tolower.c \
		ft_toupper.c \
		stack.c \
		stack2.c \
		realloc.c \
		get_next_line_utils.c \
		get_next_line.c \
		ft_matrixcpy.c \
		path.c



OBJS := $(addprefix $(OBJDIR)/,$(SRCS:%.c=%.o))

all: $(NAME)

sanitize: CFLAGS += -fsanitize=address -g3 
sanitize: $(OBJS)
	@echo "[libFT]->>\033[34m [◊] SANITIZE MODE ON [◊]\033[0m"
	$(AR) $(ARFLAGS) $(NAME) $^
	
debug: CFLAGS += -g3
debug: $(OBJS) 
	@echo "[libFT]->> \033[33m [∆] DEBUG MODE ON [∆]\033[0m"
	$(AR) $(ARFLAGS) $(NAME) $^

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJDIR): 
	mkdir $@

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
