NAME = cub3D

CC = cc
CFLAGS = -g -Wall -Wextra -Werror #-g -ggdb3 -fsanitize=address
ODIR = o-files
USER = $(shell echo $$USER)
# -L followed by the relative path of the library to link it 
LINUX_LIBRARIES = -L ./libft MLX42/libmlx42.a -lglfw -ldl
MAC_LIBRARIES = -L ./libft MLX42/libmlx42.a -lglfw -L /Users/$(USER)/.brew/lib

CFILES = \
main.c parsing.c err_exit.c


OBJECTS = $(patsubst %.c,%.o,$(CFILES))
OBJECTS := $(addprefix $(ODIR)/,$(OBJECTS))
UNAME_S := $(shell uname -s)

$(NAME): $(ODIR) $(OBJECTS) 
	@make -C ./libft
	@make -C ./MLX42

ifeq ($(UNAME_S),Linux)
	clang $(CFLAGS) $(OBJECTS) -lm $(LINUX_LIBRARIES) -o $(NAME)
else
	$(CC) $(CFLAGS) $(OBJECTS) -lm $(MAC_LIBRARIES) -o $(NAME)
endif

$(ODIR):
	@mkdir $(ODIR)

$(ODIR)/%.o: %.c
ifeq ($(UNAME_S),Linux)
	clang $(CFLAGS) -c $< -o $@
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
