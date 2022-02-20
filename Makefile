HEADER		= Map/map.hpp Stack/stack.hpp Stack/mainStack.cpp \
				Vector/vector.hpp Vector/mainVector.cpp \
                Vector/vectorIterator.hpp Iterator/iteratorTraits.hpp \
                Iterator/iterator.hpp Iterator/reverseIterator.hpp \
                Iterator/treeIterator.hpp Map/tree.hpp \
                Map/pair.hpp Map/mainMap.cpp Map/RbTreeNode.hpp main.cpp

INC			= -Iincludes/Vector -Iincludes/Map \
				-Iincludes/Stack -Iincludes/Iterator

FLAGS		= -std=c++98 -Wall -Wextra -Werror
TEST_FLAGS	= -std=c++98 -g -Wall -Wextra -Werror

CC			= clang++

all:		map vector stack

test:		$(HEADER) main.cpp
			$(CC) $(TEST_FLAGS) $(INC) main.cpp -o main_test

map:		$(HEADER) Map/mainMap.cpp
			$(CC) $(TEST_FLAGS) $(INC) Map/mainMap.cpp -o map

vector:		$(HEADER) Vector/mainVector.cpp
			$(CC) $(TEST_FLAGS) $(INC) Vector/mainVector.cpp -o vector

stack:		$(HEADER) Stack/mainStack.cpp
			$(CC) $(TEST_FLAGS) $(INC) Stack/mainStack.cpp -o stack

%.o:		%.cpp $(HEADER)
			$(CC) -g $(FLAGS) $(INC) -c $< -o $@

clean:

fclean:		clean
			rm -rf map
			rm -rf vector
			rm -rf stack
			rm -rf main_test


re:			fclean all

.PHONY:		all clean fclean re