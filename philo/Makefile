NAME = philo

CC = cc

SRC = ./source/main.c \
		./source/parsing.c \
		./source/execution1.c \
		./source/execution2.c \
		./source/execution3.c \
		./source/execution4.c \
		./source/execution5.c \
		./source/execution6.c \
		./source/execution7.c

CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
		
clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : clean all

.PHONY: clean