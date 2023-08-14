NAME            =    ../ft_printf.a
CC              =    clang
CFLAGS          =    -Wall -Wextra -Werror
SRCS            =   ft_printf.c  ft_helpers.c
libft			=	../libft.a
OBJS            = $(SRCS:.c=.o)

all:$(NAME)

# %.o: %.c
# 	gcc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@cp $(libft) $(NAME)
	@ar rcs $(NAME) $(OBJS) $(libft)
	
fclean: clean
	@rm -rf $(NAME)
	
clean:
	@rm -rf $(OBJS) $(libft)
	
re: fclean all

.PHONY: all fclean clean re