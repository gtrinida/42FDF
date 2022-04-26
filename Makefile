INC = /usr/include
INCLIB = $(INC)/minilibx-linux/lib
INCLUDES = fdf.h

MAC_MINILIBX = $(MINILIBX_DIRECTORY)libmlx.a
MAC_MINILIBX_DIRECTORY = minilibx_macos
MAC_MINILIBX_HEADERS = $(MINILIBX_DIRECTORY)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I$(INC) -g -Ilibft

NAME = fdf
SRCS = fdf.c\
 		draw_lines.c\
 		read.c\
 		utils.c\
		draw_utils.c
OBJS = $(SRCS:%.c=%.o)

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	# MacOS
	LFLAGS = -lmlx -lm -L$(MAC_MINILIBX_DIRECTORY) -framework OpenGL -framework AppKit
else
	# Linux
	LFLAGS = -Lminilibx-linux -lmlx -L$(INCLIB) -lXext -lX11 -lm -lbsd
	CFLAGS += -Iminilibx-linux
endif

%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $<

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