NAME	:= sample

SRCS	:= main.c
OBJS	:= $(SRCS:.c=.o)

CFLAGS	:= -Wall -Wextra -Werror
LIBS	:= -lmlx -lXext -lX11

.PHONY: all
all: $(NAME)

$(NAME): $(MINILIBX) $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean: $(OBJS)
	$(RM) -r $^

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all
