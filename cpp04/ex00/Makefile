NAME = a.out

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf

HEADERS = Animal.hpp Dog.hpp Cat.hpp
SRCS = main.cpp Animal.cpp Dog.cpp Cat.cpp
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
