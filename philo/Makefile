SRC=destroy.c fr_print.c ft_atol.c ft_time.c init_philos.c init_table_forks.c main.c monitor.c routine.c
OBJ=$(SRC:.c=.o)
CFLAGS= -Wall -Wextra -Werror
NAME=philo

all: $(NAME)

$(NAME): $(OBJ)
	cc $(OBJ) -o $(NAME)

%.o : %.c philo.h
	cc $(flags) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

