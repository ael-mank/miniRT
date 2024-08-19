# Variables
CC = cc
SRC_DIR = ./src/
OBJ_DIR = ./obj/
MLX_DIR = ./minilibx-linux/
MLX     = mlx_Linux
CFLAGS = -Wall -Wextra -Werror -Ilibft/include -I$(MLX_DIR) -Iinclude -g3 -lm
SRC_FILES = main \
			my_mlx/window_inputs my_mlx/my_mlx_pixel_put\
			my_mlx/write_colors \
			memory/ft_exit \
			vectors/vectors vectors/ray \
			init/init_mlx init/init init/init_objects\
			init/init_sphere init/init_pyramid \
			init/make_mat \
			render/render \
			interval/interval \
			utility/utility \
			objects/sphere objects/pyramid \
			materials/materials

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
NAME = miniRT
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
	@echo -e "$(GREEN)Built MiniLibX ✅ $(NC)"
	@cd ./libft && $(MAKE) > /dev/null && $(MAKE) bonus > /dev/null && $(MAKE) printf > /dev/null
	@echo -e "$(GREEN)Built Libft ✅ $(NC)"
	@$(CC) -Llibft -L$(MLX_DIR) -o $@ $^ -lft -lmlx $(CFLAGS) -lX11 -lXext -lm
	@echo -e "$(BLUE)Compiled $(NAME) 🎮 $(NC)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

clean:
	@$(RM) -rf $(OBJ_DIR)
	@echo -e "$(MAGENTA)Cleaned object files ✅ $(NC)"

fclean: clean
	@cd ./libft && $(MAKE) fclean > /dev/null
	@echo -e "$(MAGENTA)Cleaned libft ❎ $(NC)"
	@cd $(MLX_DIR) && $(MAKE) clean > /dev/null
	@echo -e "$(MAGENTA)Cleaned mlx ❎ $(NC)"
	@$(RM) -f $(NAME)
	@echo -e "$(MAGENTA)Cleaned $(NAME) ❎ $(NC)"

re: fclean all
