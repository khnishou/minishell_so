# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 12:11:58 by ykerdel           #+#    #+#              #
#    Updated: 2023/07/15 20:36:32 by ykerdel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=		minishell
NAME_TEST		=		test
CC				=		cc
AR				=		ar rcs
RM				=		rm -rf
CFLAGS			=		-Wall -Wextra -Werror -Ofast
LIBFT_PATH		=		libs/libft
LIBFT_LIB		=		libs/libft.a
GNL_PATH		=		libs/get_next_line
GNL_LIB			=		libs/get_next_line.a
SRC				=		$(wildcard src/*.c)
SRC_MAIN		=		main.c	$(SRC)
SRC_TEST		=		test.c	$(SRC)
OBJ				=		$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJ_DIR			=		obj

RED = \033[31m
GREEN = \033[32m
RESET = \033[0m

$(NAME) : build $(OBJ)
	@echo "----- Compiling Minishell -----"
	${CC} ${SRC_MAIN} -o ${NAME}  ${LIBFT_LIB} ${GNL_LIB} ${CFLAGS} -lreadline
	clear
	@echo "$(RED)╔═══════════════════════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(RED)║$(GREEN)                              Minishell Compiled!                              $(RED)║$(RESET)"
	@echo "$(RED)╚═══════════════════════════════════════════════════════════════════════════════╝$(RESET)"

build: $(LIBFT_PATH)
	@make -C $(LIBFT_PATH)
	@make -C $(GNL_PATH)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
	
all: ${NAME}

clean:
	@make -C $(LIBFT_PATH) clean
	rm -rf $(OBJ_DIR)
	clear

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	rm -f ${NAME}
	rm -f ${NAME_TEST}
	clear
	
re: fclean all

test: build $(OBJ)
	@echo "----- Compiling Test Minishell -----"
	@time -p (	${CC} ${SRC_TEST} -o ${NAME_TEST} ${LIBFT_LIB} ${GNL_LIB} ${CFLAGS} -lreadline)
	clear
	@echo "$(RED)╔════════════════════════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(RED)║$(GREEN)                           Compiling and Running Test ...                       $(RED)║$(RESET)"
	@echo "$(RED)╚════════════════════════════════════════════════════════════════════════════════╝$(RESET)"
	@echo
	@echo
	@./test
	@echo

valgrind :
	@valgrind --leak-check=full --show-leak-kinds=all \
	--track-origins=yes --error-limit=no --tool=memcheck -s $(NAME_TEST)

.PHONY: all install clean fclean re
