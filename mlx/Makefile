#
#

NOM=libmlx.a
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2

all: $(NOM)

$(NOM):	$(OBJ)
	@ar -rc $(NOM) $(OBJ)
	@ranlib $(NOM)
	@printf  "\033[92m\033[1:32mCompiling -------------> \033[91m$(NOM)\033[0m:\033[0m%-12s\033[32m[✔]\033[0m\n"

clean:
	@rm -f $(NOM) $(OBJ) *~
	@printf  "\033[1:32mCleaning object files -> \033[91m$(NOM)\033[0m\033[1:32m:\033[0m%-12s\033[32m[✔]\033[0m\n"

fclean: clean
	@rm -f mlx_app
	@printf  "\033[1:32mCleaning binary -------> \033[91m$(NOM)\033[0m\033[1:32m:\033[0m%-12s\033[32m[✔]\033[0m\n"

re: fclean all

.PHONY: all clean fclean re
