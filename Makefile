NAME		= minishell

TMP			= tmp

SRCS		= $(wildcard ./src/*.c)

OBJS		= $(patsubst ./src/%.c, ./$(TMP)/%.o, $(SRCS))

CC			= cc

CFALGS		= -Wall -Wextra -Werror

LIBFT		= ./libft

LINKERS		= -lft -L$(LIBFT) -lreadline -L $(HOME)/lib

INCLUDES	= -I ./include -I $(HOME)/include

RM			= rm -rf

.PHONY:		all clean fclean re

./tmp/%.o:	./src/%.c ./include/minishell.h
			@$(CC) $(CFALGS) $(INCLUDES) -o $@ -c $<

all:		$(NAME)

$(TMP):
			@mkdir $(TMP)

$(NAME):	$(TMP) $(OBJS)
			@$(MAKE) -C $(LIBFT) all
			@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LINKERS) -o $(NAME)

clean:
			@$(MAKE) -C $(LIBFT) clean
			@$(RM) $(TMP)

fclean:		clean
			@$(MAKE) -C $(LIBFT) fclean
			@$(RM) $(NAME)

re:			fclean all
