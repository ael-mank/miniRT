# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 19:43:12 by ael-mank          #+#    #+#              #
#    Updated: 2024/10/01 12:58:06 by ael-mank         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CC = cc
SRC_DIR = ./src/
OBJ_DIR = ./obj/
MLX_DIR = ./minilibx-linux/
MLX     = mlx_Linux
CFLAGS = -Wall -Wextra -Werror -Ilibft/include -I$(MLX_DIR) -Iinclude -Ofast -DSPP=100 -DMD=55
SRC_FILES = main \
            my_mlx/window_inputs my_mlx/my_mlx_pixel_put\
            my_mlx/write_colors \
            memory/ft_exit \
            vectors/vector_creation vectors/vector_properties vectors/vector_products \
			vectors/random_vectors vectors/vector_utilities \
			vectors/ray vectors/ray_sim \
            parsing/file_operations parsing/list_operations \
			parsing/parsing_helpers parsing/parsing_amb_cam \
			parsing/parsing_objects parsing/get_type\
            init/init_mlx init/init init/init_objects\
            init/init_sphere init/init_triangle\
            init/init_plane init/init_cylinder\
            init/make_mat init/make_mat2 init/init_bvh init/init_bvh2\
            render/render_lighting render/render_ray render/render_camera \
			render/render_tile render/render_utils render/render_main \
            interval/interval interval/get_intervals\
            utility/utility utility/ft_err\
            objects/sphere objects/sphere2 objects/triangle objects/triangle2\
            objects/plane objects/cylinder objects/cylinder2\
            materials/materials materials/color_val \
            materials/lights materials/ray_manip\
            aabbbvh/aabb aabbbvh/bvh aabbbvh/bvh_comp aabbbvh/bvh_comp2 \
            aabbbvh/hit_aabb 

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
NAME = miniRT_bonus
MAKE := make

GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
MAGENTA=\033[0;35m
NC=\033[0m

# Phony targets
.PHONY: all clean fclean re

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	@cd $(MLX_DIR) && ./configure > /dev/null 2>&1 
	@echo "$(GREEN)Built MiniLibX ✅ $(NC)"
	@cd ./libft && $(MAKE) > /dev/null && $(MAKE) bonus > /dev/null && $(MAKE) printf > /dev/null
	@echo "$(GREEN)Built Libft ✅ $(NC)"
	@$(CC) -Llibft -L$(MLX_DIR) -o $@ $^ -lft -lmlx $(CFLAGS) -lX11 -lXext -lm -lpthread
	@echo "$(BLUE)Compiled $(NAME) 🎮 $(NC)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

clean:
	@$(RM) -rf $(OBJ_DIR)
	@echo "$(MAGENTA)Cleaned object files ✅ $(NC)"

fclean: clean
	@cd ./libft && $(MAKE) fclean > /dev/null
	@echo "$(MAGENTA)Cleaned libft ❎ $(NC)"
	@cd $(MLX_DIR) && $(MAKE) clean > /dev/null
	@echo "$(MAGENTA)Cleaned mlx ❎ $(NC)"
	@$(RM) -f $(NAME)
	@echo "$(MAGENTA)Cleaned $(NAME) ❎ $(NC)"

re: fclean all