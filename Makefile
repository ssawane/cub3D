# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/01 16:28:48 by ssawane           #+#    #+#              #
#    Updated: 2022/08/12 20:53:20 by ssawane          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D
CC		=	gcc
HEADER	=	includes/cub3d.h
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f
LIBS	=	-L libft -lft
MN_DR	=	src/main/
PRS_DR	=	src/parse/
MAIN	=	cub3d
PARSE	=	get_next_line parsing line_checks params\
			color_checks free_funcs map_convert borders_check
SRCS	=	$(addsuffix .c, $(addprefix $(MN_DR), $(MAIN)))\
			$(addsuffix .c, $(addprefix $(PRS_DR), $(PARSE)))\
			$(addsuffix .c, temp/temp)	
OBJ		=	$(SRCS:%.c=%.o)

.PHONY	:	all clean fclean re

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			@echo "\n"
			@make -C libft
			@echo "\033[0;32mCompiling cub3D..."
			@$(CC) $(LIBS) $(CFLAGS) $(OBJ) -o $(NAME)
			@echo "\n\033[0;32mDone !"

%.o		:	%.c
			@printf "\033[0;33mGenerating cub3D objects... %-33.33s\r" $@
			@$(CC) $(CFLAGS) -c $< -o $@
			
clean	:	
			@echo "\n\033[0;31mCleaning libft..."
			@make -C libft clean
			@echo "\nRemoving binaries..."
			@$(RM) $(OBJ)
			@echo "\033[0m"

fclean	:	clean
			@echo "\033[0;31mDeleting executable..."
			@make -C libft fclean
			@$(RM) $(NAME)
			@echo "\033[0m"
			
re		:	fclean all

