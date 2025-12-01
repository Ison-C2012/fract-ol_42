NAME := fractol

CC := gcc
CFLAGS := -g3 -Wall -Wextra -Werror
IFLAGS := -Iincludes -I/home/keitotak/.local/include
MLXFLAGS := -L/home/keitotak/.local/lib -lmlx -lXext -lX11 -lm

SRCDIR := srcs
OBJDIR := objs
ARCDIR := libft

SRCS	:= 	main.c \
			check.c \
			exit.c \
			init.c \
			hook.c \
			render.c \
			fractal.c
OBJS	:= $(SRCS:%.c=$(OBJDIR)/%.o)
ARCS	:= libft.a

$(NAME): $(OBJS)
	@make -C $(ARCDIR)
	$(CC) $(CFLAGS) $^ $(ARCDIR)/$(ARCS) $(IFLAGS) $(MLXFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< $(IFLAGS) -o $@

all: $(NAME)

clean:
	@make -C $(ARCDIR) clean
	rm -rf $(OBJDIR)

fclean: clean
	@make -C $(ARCDIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
