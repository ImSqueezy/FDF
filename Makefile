NAME = fdf

ARCHIVE = warframe.a

OBJ = fdf.o parsing.o \
		get_next_line/get_next_line.o get_next_line/get_next_line_utils.o \
		
FLAGS = -c -Wall -Wextra -Werror -g

LIBFT = Libft/libft.a

LIB_MLX = minilibx-linux/libmlx_Linux.a

LIBRARIES = $(ARCHIVE) $(LIBFT) $(LIB_MLX) -lXext -lX11
COMPILE = cc $(FLAGS)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	ar r $(ARCHIVE) *.o
	cc $(LIBRARIES) -g -o $(NAME)

%.o: %.c FDF.h
	$(COMPILE) -g $<

$(LIBFT):
	make -C Libft/

clean:
	rm -f *.o $(ARCHIVE)
	rm -f Libft/*.o Libft/libft.a

fclean: clean
	rm -f $(NAME) fdf
	make fclean -C Libft/

re: fclean all

re-clean: fclean all
	rm -f *.o

.PHONY: clean

# remove -g flag and correct the check condition for argc