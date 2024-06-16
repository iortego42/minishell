NAME= minishell

CC = gcc
AR = ar
ARFLAGS = -rc
RM = rm -rf 
OBJDIR = build
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
LDFLAGS += -lreadline -L $(LFTPATH) -l$(LFTNAME) -L $(LSTRINGSPATH) -l$(LSTRINGSNAME) 

SRCS = \
		minishell.c

SRCS += parser/*.c

OBJS := $(addprefix $(OBJDIR)/,$(SRCS:%.c=%.o))


#sanitize_mini: CFLAGS += -fsanitize=address -g3
#sanitize_mini: $(OBJS) $(LFTNAME)sanitize $(LSTRINGS)sanitize banner
#	@echo "[$(NAME)]->>\033[34m [◊] SANITIZE MODE ON [◊]\033[0m"
#	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)

#debug_mini: CFLAGS += -g3
#debug_mini: $(OBJS) $(LFTNAME)debug $(LSTRINGS)debug banner
#	@echo "[$(NAME)]->>\033[33m [∆] DEBUG MODE ON [∆]\033[0m"
#	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)

$(NAME): banner $(OBJS) $(LFT) $(LSTRINGS) banner
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@
banner:
	@echo "\033[1;33m [!] WARNING [!]\033[0m\n\tWildcards are enabled\n\n\n"

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
	mkdir build/parser

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ 


clean:
	make fclean -C $(LFTPATH)
	make fclean -C $(LSTRINGSPATH)
	$(RM) $(OBJDIR)

fclean: clean_mini
	$(RM) $(NAME)

re: fclean all

red: fclean debug_mini

res: fclean sanitize_mini

.PHONY: sanitize_mini debug_mini res red re clean_mini fclean all
