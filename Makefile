NAME = cub3D

CC = gcc
CFLAGS = -g # -Wall -Wextra -Werror #-g -ggdb3 -fsanitize=address
ODIR = o-files
USER = $(shell echo $$USER)
# -L followed by the relative path of the library to link it

#LINUX_LIBRARIES = -L ./libft -lft -L ./minilibX -lmlx_Linux -Imlx_linux -lXext -lX11 -lm # OLD MLXLIB
# NEW MLXLIB: LINUX_LIBRARIES = -L ./libft -lft MLX42/libmlx42.a -lglfw -ldl
# Maybe this works for libft? -> MAC_LIBRARIES = -L ./libft -lft MLX42/libmlx42.a -lglfw -L /Users/$(USER)/.brew/lib
MAC_LIBRARIES = libft/libft.a -L ./libft -L ./mlx -lmlx -framework OpenGL -framework AppKit

CFILES = \
err_exit.c \
key_hook.c \
line.c \
main.c \
map_init.c \
move.c \
move_check.c \
parsing_map_utils_two.c \
parsing_map_utils.c \
parsing_map_validation.c \
parsing_map.c \
parsing_store_data_utils.c \
parsing_store_data.c \
parsing.c \
pixel_put.c \
player.c \
ray.c \
ray_util.c \
textures_utils.c \
textures.c \
walls.c \
window.c



OBJECTS = $(patsubst %.c,%.o,$(CFILES))
OBJECTS := $(addprefix $(ODIR)/,$(OBJECTS))
UNAME_S := $(shell uname -s)

$(NAME): $(ODIR) $(OBJECTS) 
	@make -C ./libft
#	@make -C ./mlx
	$(CC) $(CFLAGS) $(OBJECTS) $(MAC_KEYHOOK) -lm $(MAC_LIBRARIES) -o $(NAME)


$(ODIR):
	@mkdir $(ODIR)

$(ODIR)/%.o: %.c
ifeq ($(UNAME_S),Linux)
	$(CC) $(CFLAGS) -c $< -o $@
else
	$(CC) $(CFLAGS) -c $< -o $@ 
endif


.phony: all
all: $(NAME)

.phony: clean
clean: clean_libft 
	rm -f $(OBJECTS)
	rm -rf $(ODIR)

.phony: fclean
fclean: clean fclean_libft
	rm -f $(NAME) *~

.phony: re
re: fclean all

# @ makes it silence
.phony: clean_libft
clean_libft:
	@make clean -C ./libft/

.phony: fclean_libft
fclean_libft:
	@make fclean -C ./libft/
