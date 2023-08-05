NAME			=	../ft_malloc.a
CC				=	clang
CFLAGS			=	-Wall -Wextra -Werror
SRCS			=	ft_malloc.c
OBJS			=	$(SRCS:.c=.o)

all:$(NAME)

# %.o: %.c
# 	gcc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	# @cp $(NAME)
	@ar rcs $(NAME) $(OBJS)

fclean: clean
	@rm -rf $(NAME)
	
clean:
	@rm -rf $(OBJS)
	
re: fclean all

.PHONY: all fclean clean re