NAME            =    ../libft.a
CC                =    gcc
CFLAGS            =    -Wall -Wextra -Werror
FT_MALLOC_LIB	=		../ft_malloc.a

SRCS			=	ft_atoi.c		ft_calloc.c		ft_isalpha.c	ft_isdigit.c	\
					ft_memchr.c		ft_memcpy.c		ft_memset.c		ft_strlen.c		\
					ft_strnstr.c	ft_tolower.c	ft_memcmp.c		ft_toupper.c	\
					ft_bzero.c		ft_isalnum.c	ft_isascii.c	ft_isprint.c	\
					ft_memmove.c	ft_strchr.c		ft_strncmp.c	ft_strrchr.c	\
					ft_strlcpy.c	ft_strlcat.c	ft_strdup.c		ft_substr.c		\
					ft_itoa.c		ft_strjoin.c	ft_strtrim.c	ft_split.c		\
					ft_strmapi.c	ft_striteri.c	ft_putstr_fd.c	ft_putchar_fd.c	\
					ft_putendl_fd.c	ft_putnbr_fd.c	ft_delsep.c

OBJS            = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS) $(FT_MALLOC_LIB)

fclean: clean
	@rm -rf $(NAME)

clean:
	@rm -rf $(OBJS)

re: fclean all

$(OBJS): %.o:%.c ft_*.c
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all fclean clean re
