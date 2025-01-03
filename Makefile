NAME = warframe.a

OBJ = parsing.o get_next_line/get_next_line.o get_next_line/get_next_line_utils.o \
		get_next_line/get_next_line.o get_next_line/get_next_line_utils.o

FLAGS = -c -Wall -Wextra -Werror

MLIB_LIBRARIES = -I minilibx-linux/ -L minilibx-linux/ -l minilibx-linux/libmlx-linux.a \
				-L Libft/ -l Libft/Libft.a \
				-lmlx -lXext -lX11 -lft

COMPILE = cc $(FLAGS)

all: $(NAME)

$(NAME): $(OBJ)
	ar r $(NAME) *.o

%.o: %.c FDF.h
	$(COMPILE) $< $(MLIB_LIBRARIES) 

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

re-clean: fclean all
	rm -f *.o

.PHONY: clean