NAME= strings
FILENAME= lib$(NAME).a

CC = gcc
AR = ar
ARFLAGS = -rc
RM = rm -rf 
OBJDIR = build
SRCDIR = src
INCDIR = include


CFLAGS = -Wall -Wextra -Werror  -I $(INCDIR) -fsanitize=address -g3
# CFLAGS = -Wall -Wextra -Werror -I $(INCDIR) 

SRCS =	\
		io.c \
		cp.c \
		cmp.c \
		join.c \
		sub.c \
		utils.c \
		split.c \
		p_split.c \
		nsplit.c \
		rm.c \
		get_set.c \
		strings.c 

MAIN = main.c
LSTRINGSPATH = libstrings
LDFLAGS = -L . -l$(NAME)

OBJS := $(addprefix $(OBJDIR)/,$(SRCS:%.c=%.o))

all: $(NAME)

sanitize: CFLAGS += -fsanitize=address -g3 
sanitize: $(OBJS) 
	@echo "[libstrings]->>\033[34m [◊] SANITIZE MODE ON [◊]\033[0m"
	$(AR) $(ARFLAGS) $(FILENAME) $^

debug: $(OBJS)
	@echo "[libstrings]->> \033[33m [∆] DEBUG MODE ON [∆]\033[0m"
	$(AR) $(ARFLAGS) $(FILENAME) $^

$(NAME): $(FILENAME)
$(FILENAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJDIR): 
	mkdir $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ 

main: $(MAIN) $(NAME)
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o main


clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

red: fclean debug

res: fclean sanitize

.PHONY: sanitize debug res red re clean fclean all
