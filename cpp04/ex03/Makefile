NAME := a.out

CC := c++
CFLAGS := -Wall -Wextra -Werror -std=c++98
RM := rm -rf

HEADERS := AMateria.hpp
SRCS := main.cpp AMateria.cpp
OBJS := $(SRCS:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
