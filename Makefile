NAME    =  cub3d
CC := cc
CCFLAGS := -Wextra -Wall -Werror
SRC_DIR := src/
PARSING_DIR := src/parsing/
CAMERA_DIR := src/cam/
INCLUDES:= include/
CPPFLAGS := -MMD -MP


SRC := $(addprefix $(SRC_DIR), \
	main.c \
	mlx_init.c \
	mlx_free.c \
	cub3d.c \
	)

CAMERA_SRC := $(addprefix $(CAMERA_DIR), \
    camera_init.c \
    event.c \
    render.c \
    cam_mouv.c \
    keys.c \
    texture_utils.c \
	colors_utils.c \
	calc_utils.c \
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

ALL_SRC := $(SRC) $(PARSING_SRC) $(CAMERA_SRC)

OBJ_DIR := .obj/
OBJ := $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o) $(PARSING_SRC:$(PARSING_DIR)%.c=$(OBJ_DIR)parsing/%.o) $(CAMERA_SRC:$(CAMERA_DIR)%.c=$(OBJ_DIR)cam/%.o)
DEPS := $(OBJ:.o=.d)

MLX_DIR := mlx/
# MLX := $(MLX_DIR)libmlx_Linux.a
# MLX_FLAG := -L $(MLX_DIR) -lmlx_Linux -L/usr/lib -I $(MLX_DIR) -lX11 -lm -lz -lXext $(MLX)
MLX := $(MLX_DIR)libmlx_Darwin.a
MLX_FLAG := -Lmlx/ -lmlx -L/opt/X11/lib -lXext -lX11 -lm
#--> pour mac

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
	@mkdir -p $(dir $@)
	@echo "$(BLUE)...Compiling...: $< $(DEF_COLOR)"
	$(CC) $(CCFLAGS) $(CPPFLAGS) $(HEADERS) -c $< -o $@

$(OBJ_DIR)parsing/%.o: $(PARSING_DIR)%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)...Compiling...: $< $(DEF_COLOR)"
	$(CC) $(CCFLAGS) $(CPPFLAGS) $(HEADERS) -c $< -o $@

$(OBJ_DIR)cam/%.o: $(CAMERA_DIR)%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)...Compiling...: $< $(DEF_COLOR)"
	$(CC) $(CCFLAGS) $(CPPFLAGS) $(HEADERS) -c $< -o $@
	$(CC) $(CCFLAGS) $(CPPFLAGS) $(HEADERS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	@echo "$(YELLOW) 🧽 $(NAME) SUCCESSFULLY CLEANED 🧽 $(DEF_COLOR)"
	$(MAKE) kitty
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re kitty