# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abutet <abutet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 12:44:58 by abutet            #+#    #+#              #
#    Updated: 2024/04/16 12:45:00 by abutet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	./mandatory/main.c ./mandatory/utils.c ./mandatory/utils2.c

BONUS			=	./bonus/main_bonus.c ./bonus/gnl_bonus.c ./bonus/list_bonus.c ./bonus/utils_bonus.c ./bonus/here_doc_bonus.c ./bonus/family_bonus.c

OBJS			=	$(SRCS:.c=.o)

OBJS_BONUS		=	$(BONUS:.c=.o)

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror

RM				=	rm -f

NAME			=	pipex

NAME_BONUS		=	pipex_bonus

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJS)
		$(CC) $(OBJS) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS)
			$(CC) $(OBJS_BONUS) -o $(NAME_BONUS)

clean:
		$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
		$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
