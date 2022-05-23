#
#

NOM=libmlx.a
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
SRC+= mlx_png.c mlx_mouse.m
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2
RED := \033[0;31m
GREEN := \033[0;32m
NC := \033[0m

# add to match string put with X11 in size and position
CFLAGS+= -DSTRINGPUTX11

all: $(NOM)

$(NOM):	$(OBJ)
	@ar -r $(NOM) $(OBJ)
	@ranlib $(NOM)
	@echo "$(GREEN)$(NOM) created$(NC)"

%.o : %.c
	@cc -O2 -w -DSTRINGPUTX11   -c -o $@ $<

%.o : %.m
	@cc -O2 -w -DSTRINGPUTX11   -c -o $@ $<

clean:
	@rm -f $(NOM) $(OBJ) *~
	@rm -f mlx_app
	@echo "$(RED)$(NOM) deleted$(NC)"

re: clean all
