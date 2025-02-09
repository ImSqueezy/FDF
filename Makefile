NAME = fdf 

OBJS = main.o parsing.o utils.o drawing.o color_definition.o drawing_utils.o \
	mlx_connection.o hooks.o rotation_utils.o mem_related.o \
	get_next_line/get_next_line.o get_next_line/get_next_line_utils.o

LIBFT_SRCS = $(addprefix Libft/, ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o ft_strlen.o ft_memset.o ft_bzero.o \
	ft_memcpy.o ft_memmove.o ft_strlcpy.o ft_strlcat.o ft_toupper.o ft_tolower.o ft_strchr.o ft_strrchr.o ft_strncmp.o \
	ft_memchr.o ft_memcmp.o ft_strnstr.o ft_atoi.o ft_strdup.o ft_calloc.o ft_substr.o ft_substr.o ft_strjoin.o ft_strtrim.o \
	ft_split.o ft_itoa.o ft_strmapi.o ft_striteri.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o)

LIBFT = Libft/libft.a

MLX_LIB = minilibx-linux/libmlx_Linux.a
MLX_F = -lXext -lX11

FLAGS = -Wall -Wextra -Werror
COMPILE = cc $(FLAGS)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	cc $(OBJS) $(LIBFT) $(MLX_LIB) $(MLX_F) -lm -o $(NAME) 

$(LIBFT): $(LIBFT_SRCS)
	make -C Libft/

%.o: %.c FDF.h Libft/libft.h get_next_line/get_next_line.h
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