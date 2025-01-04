NAME = warframe.a

OBJ = parsing.o get_next_line/get_next_line.o get_next_line/get_next_line_utils.o \
		get_next_line/get_next_line.o get_next_line/get_next_line_utils.o

FLAGS = -c -Wall -Wextra -Werror

LIBRARIES = -I minilibx-linux/ -L minilibx-linux/ -l minilibx-linux/libmlx-linux.a \
				-L Libft/ -l Libft/Libft.a \
				-lmlx -lXext -lX11

LIBFT = Libft/libft.a

COMPILE = cc $(FLAGS)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	ar r $(NAME) *.o
	ar r $(NAME) $(LIBFT)

%.o: %.c FDF.h
	$(COMPILE) $< $(MLIB_LIBRARIES)

$(LIBFT):
	make -C Libft/

clean:
	rm -f *.o
	rm -f Libft/*.o

fclean: clean
	rm -f $(NAME)
	make fclean -C Libft/

re: fclean all

re-clean: fclean all
	rm -f *.o

.PHONY: clean