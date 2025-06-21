NAME = PmergeMe

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf

HEADERS = Timer.hpp \
	ISortStrategy.hpp JacobsthalDecreasingGenerator.hpp \
	vector_merge_insertion/VectorMergeInsertion.hpp vector_merge_insertion/VectorChunk.hpp \
	deque_merge_insertion/DequeMergeInsertion.hpp deque_merge_insertion/DequeChunk.hpp

SRCS = main.cpp Timer.cpp print_result_details.cpp \
	ISortStrategy.cpp JacobsthalDecreasingGenerator.cpp \
	vector_merge_insertion/VectorMergeInsertion.cpp vector_merge_insertion/VectorChunk.cpp \
	deque_merge_insertion/DequeMergeInsertion.cpp deque_merge_insertion/DequeChunk.cpp

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
