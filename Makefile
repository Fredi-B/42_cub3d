NAME = cub3D
BONUS = cub3D_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SDIR = ./src
SDIR_BONUS = ./src_bonus
ODIR = obj
ODIR_BONUS = obj_bonus

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

CFILES_BONUS = $(patsubst %.c,%_bonus.c,$(CFILES)) \
move_race_bonus.c \
move_race_utils_bonus.c

OBJECTS = $(patsubst %.c,%.o,$(CFILES))
OBJECTS := $(addprefix $(ODIR)/,$(OBJECTS))

OBJECTS_BONUS = $(patsubst %.c,%.o,$(CFILES_BONUS))
OBJECTS_BONUS := $(addprefix $(ODIR_BONUS)/,$(OBJECTS_BONUS))

$(NAME): $(ODIR) $(OBJECTS) 
	@make -C ./libft
	$(CC) $(CFLAGS) $(OBJECTS) $(MAC_KEYHOOK) -lm $(MAC_LIBRARIES) -o $(NAME)

$(ODIR):
	@mkdir $(ODIR)

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

$(BONUS): $(ODIR_BONUS) $(OBJECTS_BONUS)
	@make -C ./libft
	$(CC) $(CFLAGS) $(OBJECTS_BONUS) -lm $(MAC_LIBRARIES) -o $(BONUS)

$(ODIR_BONUS):
	@mkdir $(ODIR_BONUS)

$(ODIR_BONUS)/%.o: $(SDIR_BONUS)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.phony: all
all: $(NAME) $(BONUS)

.phony: BONUS
bonus: $(BONUS)

.phony: clean_all
clean_all: clean clean_bonus

.phony: fclean_all
fclean_all: fclean fclean_bonus

.phony: clean
clean: clean_libft 
	@rm -f $(OBJECTS) $(OBJECTS_BONUS)
	@rm -rf $(ODIR) $(ODIR_BONUS)

.phony: fclean
fclean: clean fclean_libft
	@rm -f $(NAME) $(BONUS) *~

.phony: clean_bonus
clean_bonus: clean_libft 
	@rm -f $(OBJECTS_BONUS)
	@rm -rf $(ODIR_BONUS)

.phony: fclean_bonus
fclean_bonus: clean_bonus fclean_libft
	@rm -f $(BONUS) *~

.phony: re
re: fclean all

# @ makes it silence
.phony: clean_libft
clean_libft:
	@make clean -C ./libft/

.phony: fclean_libft
fclean_libft:
	@make fclean -C ./libft/
