NAME = PmergeMe

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf

HEADERS = ISortStrategy.hpp VectorMergeInsertion.hpp DequeMergeInsertion.hpp VectorChunk.hpp JacobsthalDecreasingGenerator.hpp
SRCS = main.cpp ISortStrategy.cpp VectorMergeInsertion.cpp DequeMergeInsertion.cpp VectorChunk.cpp JacobsthalDecreasingGenerator.cpp
OBJS = $(SRCS:%.cpp=%.o)

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
