OBJS = get_next_line.o get_next_line_utils.o

FLAGS = -Wall -Wextra -Werror -c

COMPILE = cc $(FLAGS)

NAME = gnl.a

all: get_next_line.h $(NAME)

$(NAME): $(OBJS)

bonus: $(B_OBJS)

%.o: %.c get_next_line.h
	$(COMPILE) $<
	@ar r $(NAME) $@

re: clean all

clean:
	@rm -f $(OBJS) $(B_OBJS)

fclean: clean
	@rm -f $(NAME)

.PHONY: clean