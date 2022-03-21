NAME = a.out
SRCS = get_next_line.c get_next_line_utils.c
CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS)

fclean:
	rm -f $(NAME)

re: fclean all