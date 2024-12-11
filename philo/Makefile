# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 11:21:34 by msavelie          #+#    #+#              #
#    Updated: 2024/12/11 11:50:13 by msavelie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

NAME = philo

SRCS = \
	main.c \
	parse.c \
	utils.c \
	error.c

OBJS = ${SRCS:.c=.o}

CFLAGS = -g -Wall -Werror -Wextra

RM = rm -rf

.PHONY = all clean fclean re

all: ${NAME}

${NAME}: ${OBJS}
	@echo "$(BLUE)🛠  Compiling philosophers... 🛠$(DEF_COLOR)"
	@cc ${CFLAGS} ${OBJS} -o ${NAME}
	@echo "$(GREEN)🥳 Success!🥳$(DEF_COLOR)"

%.o: %.c
	@cc $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)🚽 Deleting object files... 🚽$(DEF_COLOR)"
	@${RM} ${OBJS}

fclean: clean
	@echo "$(RED)🪦 Deleting philosophers... 🪦$(DEF_COLOR)"
	@${RM} ${NAME}
	@echo "$(RED)☣️  CLEAR ☣️$(DEF_COLOR)"

re: fclean all