NAME = libia.a

DEF = \033[0m
GRA = \033[1m
SOU = \033[4m
BLI = \033[5m
BLA = \033[30m
RED = \033[31m
GRE = \033[32m
YEL = \033[33m
BLU = \033[34m
PUR = \033[35m
CYA = \033[36m
WHI = \033[37m
ORG = \033[1;31m

SRCS_UTILITIES_NAME = display_info.c \
					  activation.c \
					  init_network.c \
					  init_neurone.c \
					  firing.c \
					  export_weight.c \
					  database.c \
					  reset_nw.c \
					  import_weight.c

SRCS_GENETIC_NAME =

SRCS_BACKP_NAME = backp.c \
				  calculus.c \
				  apply_grad.c \
				  fct.c

SRCS_GENETIC_PATH = srcs/training/genetic/

SRCS_BACKP_PATH = srcs/training/backp/

SRCS_UTILITIES_PATH = srcs/utilities/

INC = includes/libia.h includes/neural_network.h

INC_PATH = includes/

FLAG = -Wall -Wextra -Werror -O1 -O2 -O3 -Ofast -march=native 

SRCS_UTILITIES = $(addprefix $(SRCS_UTILITIES_PATH), $(SRCS_UTILITIES_NAME))

SRCS_GENETIC = $(addprefix $(SRCS_GENETIC_PATH), $(SRCS_GENETIC_NAME))

SRCS_GENETIC = $(addprefix $(SRCS_BACKP_PATH), $(SRCS_BACKP_NAME))

SRCS_PATH = srcs/

SRCS = $(SRCS_UTILITIES)
SRCS += $(SRCS_GENETIC)
SRCS += $(SRCS_BACKP)

OBJS_UTILITES = $(SRCS_UTILITIES:.c=.o)

OBJS_GENETIC = $(SRCS_GENETIC:.c=.o)

OBJS_BACKP = $(SRCS_BACKP:.c=.o)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS_UTILITES) $(OBJS_BACKP) $(OBJS_GENETIC) $(INC)
	@echo "Making $(RED)$(SOU)Libia$(DEF)$(RED)...$(DEF)"
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	
	@echo "$(GRE)Done !$(DEF)"

$(SRCS_UTILITIES_PATH)%.o: $(SRCS_UTILITIES_PATH)%.c $(INC)
	@gcc $(FLAG) -c $< -o $@ -I $(INC_PATH)

$(SRCS_GENETIC_PATH)%.o: $(SRCS_GENETIC_PATH)%.c $(INC)
	@gcc $(FLAG) -c $< -o $@ -I $(INC_PATH)

$(SRCS_BACKP_PATH)%.o: $(SRCS_BACKP_PATH)%.c $(INC)
	@gcc $(FLAG) -c $< -o $@ -I $(INC_PATH)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@echo "$(RED)Libia$(DEF) deleted"
	@rm -rf $(NAME)

re: fclean all
