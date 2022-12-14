CFLAGS = -Wall -Wextra -Werror 
CPPFLAGS = -I$(shell brew --prefix readline)/include -Iincludes
LDFLAGS = -L$(shell brew --prefix readline)/lib -L$(LIBFT_DIR)
LDLIBS = -lreadline -lhistory -lft
NAME = minishell
NAME_DEBUG = minishell_debug
SRCS =	main.c																		\
		ctrl_signal.c																\
		echo.c env_vars_utils.c export.c unset.c pwd.c cd.c env.c exit.c			\
		lexer.c	state_general.c print_lexer.c state_quote.c							\
		parser.c parser_utils.c print_ast.c node.c									\
		expansion.c expand.c expand_str.c expand_env.c								\
		execution.c builtin.c bin.c	pipe.c	redirect.c	redirect_here.c	backup_fd.c	\
		stat.c utils.c put_error.c arg.c set_var.c									\
		wopen.c	wclose.c wpipe.c wfork.c wwaitpid.c wdup2.c	ft_wcalloc.c			\

OBJ = $(addprefix $(OBJDIR)/, $(SRCS:%.c=%.o))
OBJDIR = obj
VPATH = srcs srcs/lexer srcs/parser srcs/expansion srcs/execution srcs/builtin srcs/utils srcs/wfuncs

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
	@echo > ~/.inputrc set echo-control-characters off

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

test:
	bash tests/expansion.sh
	bash tests/exec.sh

re: fclean all