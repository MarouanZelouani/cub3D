NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes
LIBFT_DIR = ./libft
HEADER = 
LIBFT = $(LIBFT_DIR)/libft.a
SRC_DIR = ./src/ 
BIN_DIR = bin

SRC:= $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.c)) 
OBJ:= $(patsubst %.c, $(BIN_DIR)/%.o, $(notdir $(SRC)))

vpath %.c $(SRC_DIR)

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
 
$(LIBFT) :
	make -C $(LIBFT_DIR)

$(BIN_DIR) :
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/%.o: %.c | $(BIN_DIR)
	$(CC) $(FLAGS) -c -o $@ $<

re : fclean all

clean : 
	make -C $(LIBFT_DIR) clean
	rm -rf  $(BIN_DIR)

fclean : clean
	make -C $(LIBFT_DIR) fclean
	rm -rf $(NAME)

.PHONY: re all clean fclean 
.SECOUNDARY: 