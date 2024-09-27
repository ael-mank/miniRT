# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 19:43:12 by ael-mank          #+#    #+#              #
#    Updated: 2024/09/27 21:00:33 by ael-mank         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CC = cc
SRC_DIR = ./src/
OBJ_DIR = ./obj/
MLX_DIR = ./minilibx-linux/
MLX     = mlx_Linux
CFLAGS = -Wall -Wextra -Werror -Ilibft/include -I$(MLX_DIR) -Iinclude -Ofast
SRC_FILES = main \
            my_mlx/window_inputs my_mlx/my_mlx_pixel_put\
            my_mlx/write_colors \
            memory/ft_exit \
            vectors/vectors vectors/ray \
            parsing/file_parsing1 parsing/file_parsing2\
            parsing/file_parsing3 parsing/file_parsing4\
			parsing/file_parsing5 \
            init/init_mlx init/init init/init_objects\
            init/init_sphere init/init_triangle\
            init/init_plane init/init_cylinder\
            init/make_mat init/make_mat2 init/init_bvh init/init_bvh2\
            render/render \
            interval/interval interval/get_intervals\
            utility/utility utility/ft_err\
            objects/sphere objects/triangle \
            objects/plane objects/cylinder\
            materials/materials materials/color_val \
            materials/lights materials/ray_manip\
            aabbbvh/aabb aabbbvh/bvh aabbbvh/bvh_comp aabbbvh/bvh_comp2 \
            aabbbvh/hit_aabb 

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
NAME = miniRT
BONUS_NAME = miniRT_bonus
MAKE := make

GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
MAGENTA=\033[0;35m
NC=\033[0m

# Phony targets
.PHONY: all bonus clean fclean re

# Rules
all: CFLAGS += -DSPP=1 -DMD=2
all: clean $(NAME)

bonus: CFLAGS += -DSPP=10 -DMD=55
bonus: clean $(BONUS_NAME)

$(NAME): $(OBJ)
	@cd $(MLX_DIR) && ./configure > /dev/null 2>&1 
	@echo -e "$(GREEN)Built MiniLibX ✅ $(NC)"
	@cd ./libft && $(MAKE) > /dev/null && $(MAKE) bonus > /dev/null && $(MAKE) printf > /dev/null
	@echo -e "$(GREEN)Built Libft ✅ $(NC)"
	@$(CC) $(CFLAGS) -Llibft -L$(MLX_DIR) -o $@ $^ -lft -lmlx -lX11 -lXext -lm -lpthread
	@echo -e "$(BLUE)Compiled $(NAME) 🎮 $(NC)"

$(BONUS_NAME): $(OBJ)
	@cd $(MLX_DIR) && ./configure > /dev/null 2>&1 
	@echo -e "$(GREEN)Built MiniLibX ✅ $(NC)"
	@cd ./libft && $(MAKE) > /dev/null && $(MAKE) bonus > /dev/null && $(MAKE) printf > /dev/null
	@echo -e "$(GREEN)Built Libft ✅ $(NC)"
	@$(CC) $(CFLAGS) -Llibft -L$(MLX_DIR) -o $@ $^ -lft -lmlx -lX11 -lXext -lm -lpthread
	@echo -e "$(BLUE)Compiled $(BONUS_NAME) 🎮 $(NC)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -rf $(OBJ_DIR)
	@echo -e "$(MAGENTA)Cleaned object files ✅ $(NC)"

fclean: clean
	@cd ./libft && $(MAKE) fclean > /dev/null
	@echo -e "$(MAGENTA)Cleaned libft ❎ $(NC)"
	@cd $(MLX_DIR) && $(MAKE) clean > /dev/null
	@echo -e "$(MAGENTA)Cleaned mlx ❎ $(NC)"
	@$(RM) -f $(NAME) $(BONUS_NAME)
	@echo -e "$(MAGENTA)Cleaned $(NAME) and $(BONUS_NAME) ❎ $(NC)"

re: fclean all