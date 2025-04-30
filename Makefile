CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRC = src/pipex.c
OBJ = $(SRC:.c=.o)
NAME = pipex
LIB_DIR = lib
LIB_NAME = libft.a

all: $(LIB_DIR)/$(LIB_NAME) $(NAME)

$(LIB_DIR)/$(LIB_NAME):
	$(MAKE) -C $(LIB_DIR)

$(NAME): $(OBJ) $(LIB_DIR)/$(LIB_NAME)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIB_DIR) -lft

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all