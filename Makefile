CFLAGS = 
# CFLAGS = -Wall -Wextra -Werror 
CPPFLAGS = -L$(shell brew --prefix readline)/lib -lreadline -lhistory -I $(shell brew --prefix readline)/include -I includes
NAME = minishell
SRCS = $(shell cd srcs && echo *.c)
OBJ = $(addprefix $(OBJDIR)/, $(SRCS:%.c=%.o))
OBJDIR = obj
VPATH = srcs

## libft ##
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
###########

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CPPFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

$(LIBFT):
	make bonus -C $(LIBFT_DIR)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(NAME)

re: fclean all