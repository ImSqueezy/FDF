NAME = fdf 

OBJS = main.o parsing.o utils.o drawing.o hooks.o \
	get_next_line/get_next_line.o get_next_line/get_next_line_utils.o \

LIBFT_SRCS = $(wildcard Libft/*.c)
LIBFT = Libft/libft.a

MLX_LIB = minilibx-linux/libmlx_Linux.a
MLX_F = -lXext -lX11 -lm 

FLAGS = -g
# -Wall -Wextra -Werror 
COMPILE = cc $(FLAGS)

$(NAME): $(LIBFT) $(OBJS)
	cc $(OBJS) $(LIBFT) $(MLX_LIB) $(MLX_F) -g -o $(NAME)

$(LIBFT): $(LIBFT_SRCS)
	make -C Libft/

%.o: %.c FDF.h Libft/libft.h
	$(COMPILE) -c $< -o $@

clean:
	rm -f $(OBJS)
	make clean -C Libft

fclean: clean
	rm -f $(NAME)
	make fclean -C Libft

re: fclean $(NAME)

re-clean: fclean $(NAME)
	rm -f $(OBJS)

.PHONY: clean