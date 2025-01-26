NAME = a.out

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf

HEADERS = ClapTrap.hpp ScavTrap.hpp FlagTrap.hpp
SRCS = main.cpp ClapTrap.cpp ScavTrap.cpp FlagTrap.cpp
OBJS = $(SRCS:%.cpp=%.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
