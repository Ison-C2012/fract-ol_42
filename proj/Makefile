NAME := fractol

CFLAGS := -Wall -Wextra -Werror
MLXFLAGS := -lmlx -lXext -lX11 -lm

SRCDIR := srcs
OBJDIR := objs
INCDIR := includes
ARCDIR := libft

SRCS	:= 	coord.c \
			hook.c \
			julia.c \
			main.c \
			mandelbrot.c \
			render.c
OBJS	:= $(SRCS:%.c=$(OBJDIR)/%.o)
ARCS	:= libft.a

$(NAME): $(OBJS)
	@make -C $(ARCDIR)
	$(CC) $(CFLAGS) $^ $(ARCDIR)/$(ARCS) $(MLXFLAGS) -I $(INCDIR) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< $(MLXFLAGS) -I $(INCDIR) -o $@

all: $(NAME)

clean:
	@make -C $(ARCDIR) clean
	rm -rf $(OBJDIR)

fclean: clean
	@make -C $(ARCDIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
