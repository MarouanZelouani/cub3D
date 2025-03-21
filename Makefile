NAME = cub3D
CC = cc -Wall -Wextra -Werror -g
SRC = 	./src/main.c\
		./src/textures.c\
		./src/ray.c\
		./src/3D_map.c \
		./src/minimap.c\
		./src/hook.c\
		./parsing/parsing.c\
		./parsing/parsing2.c\
		./parsing/rgb.c\
		./parsing/tool.c\
		./parsing/map_parsing.c\
		./parsing/tools2.c\
		./parsing/space.c\
		./parsing/zero.c\
		./parsing/validation.c				
OBJ = $(SRC:.c=.o)
LIB = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	$(CC) $(OBJ) $(LIB) libmlx.a -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c
	$(CC) -I/usr/include -O3 -c $< -o $@
	
clean:
	make -C ./libft clean
	@rm -rf $(OBJ)

fclean: clean
	make -C ./libft fclean
	@rm -rf $(NAME)

re: fclean all
