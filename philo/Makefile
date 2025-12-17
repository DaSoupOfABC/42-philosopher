NAME		= philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

SRC_DIR		= src
INC_DIR		= .

SRCS		= $(SRC_DIR)/main.c \
			  $(SRC_DIR)/checks.c \
			  $(SRC_DIR)/helpers.c \
			  $(SRC_DIR)/init.c \
			  $(SRC_DIR)/init_philo.c \
			  $(SRC_DIR)/monitor.c \
			  $(SRC_DIR)/philosopher_routine.c \
			  $(SRC_DIR)/simulation.c \
			  $(SRC_DIR)/thread_helpers.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re