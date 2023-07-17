NAME            =    ../get_next_line.a
CC                =    gcc
CFLAGS            =    -Wall -Wextra -Werror

SRCS			=	get_next_line_utils.c		get_next_line.c

OBJS            = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

fclean: clean
	@rm -rf $(NAME)

clean:
	@rm -rf $(OBJS)

re: fclean all

.PHONY: all fclean clean re
