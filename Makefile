INC = .
INCLUDES = fdf.h
MINILIBX = $(MINILIBX_DIRECTORY)libmlx.a
MINILIBX_DIRECTORY = minilibx_macos
MINILIBX_HEADERS = $(MINILIBX_DIRECTORY)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INC) -g -Ilibft

NAME = fdf
SRCS = fdf.c\
 		draw_lines.c\
 		read.c\
 		utils.c\
		draw_utils.c
OBJS = $(SRCS:%.c=%.o)

LFLAGS = -lmlx -lm -L$(MINILIBX_DIRECTORY) -framework OpenGL -framework AppKit

$(NAME): $(OBJS)
	@make -C libft
	$(CC) -o $(NAME) $(OBJS) $(LFLAGS) libft/libft.a

all: $(NAME)

clean:
	@make -C libft clean
	$(RM) $(OBJS)

fclean: clean
	@make -C minilibx_macos clean
	@make -C libft fclean
	$(RM) $(NAME)

re: clean all

norme:
	norminette $(SRCS) fdf.h
	norminette libft/*.c libft/*.h
