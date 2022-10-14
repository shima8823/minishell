CFLAGS = 
# CFLAGS = -Wall -Wextra -Werror 
CPPFLAGS = -I$(shell brew --prefix readline)/include -Iincludes
LDFLAGS = -L$(shell brew --prefix readline)/lib -L$(LIBFT_DIR)
LDLIBS = -lreadline -lhistory -lft
NAME = minishell
NAME_DEBUG = minishell_debug
SRCS =	main.c										\
		ctrl_signal.c								\
		echo.c env_vars_utils.c export.c export2.c	\
		lexer.c	state_general.c print_lexer.c state_quote.c	\
		parser.c print_ast.c node.c					\
		execution.c builtin.c bin.c					\
		expansion.c	\
		stat.c utils.c

OBJ = $(addprefix $(OBJDIR)/, $(SRCS:%.c=%.o))
OBJDIR = obj
VPATH = srcs srcs/lexer srcs/parser srcs/expansion srcs/execution srcs/builtin srcs/utils

## libft ##
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
###########

ifdef DEBUGMODE
NAME = $(NAME_DEBUG)
CFLAGS += -D DEBUG=1
endif

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(LDFLAGS) -o $(NAME) $(OBJ) $(LDLIBS)

$(LIBFT):
	make bonus -C $(LIBFT_DIR)

$(OBJDIR)/%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(NAME)
	$(RM) $(NAME_DEBUG)

debug: clean
	@make DEBUGMODE=1
	$(MAKE) clean

leak: clean
	$(MAKE) NAME="minishell_leak"
	$(MAKE) CFLAGS="$(CFLAGS) -fsanitize=address"
	$(MAKE) clean

re: fclean all