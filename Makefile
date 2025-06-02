NAME    =  cub3d
CC := gcc
CCFLAGS := -Wextra -Wall -Werror -g3
SRC_DIR := src/
PARSING_DIR := src/parsing/
INCLUDES:= include/

SRC := $(addprefix $(SRC_DIR), \
	main.c \
	mlx_init.c \
	event.c \
	render.c \
	camera_init.c \
	)

PARSING_SRC := $(addprefix $(PARSING_DIR), \
	parse_color.c \
	parse_config.c \
	parse_file.c \
	parse_map.c \
	check_map.c \
	error.c \
	cleanup.c \
	init.c \
	tools.c \
	free.c\
	utils.c \
	)

ALL_SRC := $(SRC) $(PARSING_SRC)

OBJ_DIR := .obj/
OBJ := $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o) $(PARSING_SRC:$(PARSING_DIR)%.c=$(OBJ_DIR)parsing/%.o)

MLX_DIR := mlx/
MLX := $(MLX_DIR)libmlx_Linux.a
MLX_FLAG := -L $(MLX_DIR) -lmlx_Linux -L/usr/lib -I $(MLX_DIR) -lX11 -lm -lz -lXext $(MLX)

LIBFT_DIR := libft/
LIBFT := $(LIBFT_DIR)libft.a
LIBFT_FLAG := -L $(LIBFT_DIR) $(LIBFT)

HEADERS:= -I $(INCLUDES) -I $(MLX_DIR) -I $(LIBFT_DIR)

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
PURPLE=\033[35m

$(NAME): $(OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CCFLAGS) $(OBJ) $(MLX_FLAG) $(LIBFT_FLAG) -o $(NAME)
	@echo "$(PURPLE) ✨ $(NAME) COMPILED ✨$(DEF_COLOR)"
	$(MAKE) kitty

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)...Compiling...: $< $(DEF_COLOR)"
	$(CC) $(CCFLAGS) $(HEADERS) -c $< -o $@

$(OBJ_DIR)parsing/%.o: $(PARSING_DIR)%.c
	@mkdir -p $(OBJ_DIR)parsing
	@echo "$(BLUE)...Compiling...: $< $(DEF_COLOR)"
	$(CC) $(CCFLAGS) $(HEADERS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	@echo "$(YELLOW) 🧽 $(NAME) SUCCESSFULLY CLEANED 🧽 $(DEF_COLOR)"
	$(MAKE) kitty
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re kitty