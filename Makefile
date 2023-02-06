NAME		=	so_long

GNL_PATH	=	GNL/

GNL_FILES	=	get_next_line_utils.c get_next_line.c ft_itoa.c ft_strncmp.c
GNL_OBJS	=	$(addprefix $(GNL_PATH), $(GNL_FILES:.c=.o))

FILES		=	so_long.c game.c map.c events.c checkers.c window.c
OBJS		=	$(FILES:.c=.o)

CFLAGS		=	-Wall -Werror -Wextra -g3

MLX_FLAGS	=	-lmlx -lX11 -Imlx -lXext

%.o: %.c 
	cc $(CFLAGS) -c $<  -o $@
	
all: $(NAME)

$(NAME): $(GNL_OBJS) $(OBJS)
	cc $(CFLAGS) $^ $(MLX_FLAGS) -o $@

clean: 
	rm -f $(GNL_OBJS) $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re