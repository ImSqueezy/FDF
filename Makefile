NAME = warframe.a
OBJ = main.o
FLAGS = -c -Wall -Wextra -Werror
MLIB_LIBRARIES = -I minilibx-linux/ -L minilibx-linux/ -lmlx -lXext -lX11
COMPILE = cc $(FLAGS)

all: $(NAME)

$(NAME): $(OBJ)
	ar r $(NAME) $(OBJ)

%.o: %.c FDF.h
	$(COMPILE) $< $(MLIB_FLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: clean