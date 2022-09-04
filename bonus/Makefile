# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/01 16:28:48 by ssawane           #+#    #+#              #
#    Updated: 2022/09/04 14:22:44 by ssawane          ###   ########.fr        #
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
			$(addsuffix .c, $(addprefix $(RND_DR), $(RENDER)))\
			$(addsuffix .c, temp/temp)	
OBJ		=	$(SRCS:%.c=%.o)

.PHONY	:	all clean fclean

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			@make -C libft
			@make -C minilibx
			@$(CC) $(CFLAGS) $(LIBS) $(OBJ) -o $(NAME)

%.o		:	%.c
			@$(CC) $(CFLAGS) -c $< -o $@
			
clean	:	
			@make -C libft clean
			@$(RM) $(OBJ)

fclean	:	clean
			@make -C libft fclean
			@$(RM) $(NAME)

