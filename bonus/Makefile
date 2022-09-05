# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/01 16:28:48 by ssawane           #+#    #+#              #
#    Updated: 2022/09/05 15:59:42 by ssawane          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	../cub3D_bonus
CC		=	gcc
HEADER	=	includes/cub3d.h
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f
LIBS	=	-L libft -lft -L minilibx -lmlx -framework OpenGL -framework AppKit
MN_DR	=	src/main/
PRS_DR	=	src/parse/
RND_DR	=	src/rendering/
MAIN	=	cub3d
RENDER	=	play_it buttonhooks raycast raycast_texture close_hook doors minimap
PARSE	=	get_next_line parsing line_checks params\
			color_checks free_funcs map_convert borders_check
SRCS	=	$(addsuffix .c, $(addprefix $(MN_DR), $(MAIN)))\
			$(addsuffix .c, $(addprefix $(PRS_DR), $(PARSE)))\
			$(addsuffix .c, $(addprefix $(RND_DR), $(RENDER)))
OBJ		=	$(SRCS:%.c=%.o)

.PHONY	:	all clean fclean

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			@echo "\n"
			@make -C libft
			@make -C minilibx
			@echo "\033[0;32mCompiling cub3D BONUS..."
			@$(CC) $(CFLAGS) $(LIBS) $(OBJ) -o $(NAME)
			@echo "\n\033[0;32mDone !"

%.o		:	%.c $(HEADER)
			@printf "\033[0;33mGenerating cub3D BONUS objects... %-33.33s\r" $@
			@$(CC) $(CFLAGS) -c $< -o $@
			
clean	:	
			@make -C libft clean
			@make -C minilibx clean
			@$(RM) $(OBJ)

fclean	:	clean
			@make -C libft fclean
			@$(RM) $(NAME)

