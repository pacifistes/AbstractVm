NAME = abstractVm
FLAGS = -std=c++14 -Wall -Wextra -Werror
INCLUDE = includes/
SRCSPATH = srcs/
SRCS = Operand.cpp OperandFactory.cpp Stack.cpp StackManager.cpp eOperandType.cpp main.cpp
OBJ= $(SRC:.cpp=.o)
CC = clang++

SRC = $(addprefix $(SRCSPATH), $(SRCS))

%.o: %.cpp
	$(CC) -I $(INCLUDE) -c $(FLAGS)  $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -I $(INCLUDE) -o $(NAME) $(OBJ) 

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(NAME) $(OBJ)

re: fclean all

.PHONY: all clean fclean re