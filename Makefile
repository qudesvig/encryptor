NAME= encryptor

SRCS_PATH= srcs/

SRCS_NAME= main.c \
		   encryptor.c \
		   filling_netw.c \
		   display.c \
		   training.c \
		   gang_bang.c \
		   evolve.c \
		   get_elit.c \
		   comeback.c \
		   testing_pop.c \
		   saving.c \
		   free_env.c \
		   fct.c

SRCS= $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS= $(SRCS_NAME:.c=.o)

INC= includes/encryptor.h

LIB= libft/libft.a

LIBIA= libia/libia.a

CC= gcc

FLAGS= -Wall -Wextra -Werror -O1 -O2 -O3 -Ofast -march=native

all: $(NAME)

$(NAME): $(LIBIA) $(LIB) $(OBJS) $(INC)
	@$(CC) $(FLAGS) -lpthread  -o $(NAME) $(OBJS) $(LIBIA) $(LIB)


%.o: $(SRCS_PATH)/%.c $(INC)
	@$(CC) $(FLAGS) -c $< -o $@

$(LIBIA): $(LIB) FORCE
	@make -C libia/

fsanitize: $(SRCS)
	gcc -g3 -fsanitize=address $(SRCS) $(LIB) $(LIBIA)

$(LIB): FORCE
	@make -C libft

FORCE:

clean:
	@rm -rf $(OBJS)
	@make -C libft/ clean
	@make -C libia/ clean

fclean: clean
	@rm -rf $(NAME)
	@make -C libft/ fclean
	@make -C libia/ fclean

re: fclean all
