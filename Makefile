
FAIL =\033[91m
GREEN =\033[32m
OKCYAN =\033[96m
WARNING =\033[93m
RESET =\033[0m

CXX = clang++
# SANFLAGS = -fsanitize=address
DEBUGFLAGS = -g -fno-limit-debug-info
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 $(DEBUGFLAGS) $(SANFLAGS) -O3

SRC = \
	test/ft_main_vector.cpp		test/std_main_vector.cpp	\
	test/ft_main_map.cpp		test/std_main_map.cpp		\
	test/ft_main_stack.cpp		test/std_main_stack.cpp		\

OBJ = $(SRC:.cpp=.o)
# =======================================SETTING===============================================================

FT_VECTOR = ft_vector
STD_VECTOR = std_vector
VECTOR = vector

FT_MAP = ft_map
STD_MAP = std_map
MAP = map

FT_STACK = ft_stack
STD_STACK = std_stack
STACK = stack

# =======================================Run===================================================================

all: $(FT_VECTOR) $(STD_VECTOR) $(FT_MAP) $(STD_MAP) $(FT_STACK) $(STD_STACK)

# ================Compile==================
$(FT_VECTOR) : vector.hpp test/ft_main_vector.cpp Makefile
	$(CXX) test/ft_main_vector.cpp $(CXXFLAGS) -o $(FT_VECTOR)

$(STD_VECTOR) : vector.hpp test/std_main_vector.cpp Makefile
	$(CXX) test/std_main_vector.cpp $(CXXFLAGS) -o $(STD_VECTOR)

$(FT_MAP) : map.hpp test/ft_main_map.cpp Makefile
	$(CXX) test/ft_main_map.cpp $(CXXFLAGS) -o $(FT_MAP)

$(STD_MAP) : map.hpp test/std_main_map.cpp Makefile
	$(CXX) test/std_main_map.cpp $(CXXFLAGS) -o $(STD_MAP)

$(FT_STACK) : stack.hpp test/ft_main_stack.cpp Makefile
	$(CXX) test/ft_main_stack.cpp $(CXXFLAGS) -o $(FT_STACK)

$(STD_STACK) : stack.hpp test/std_main_stack.cpp Makefile
	$(CXX) test/std_main_stack.cpp $(CXXFLAGS) -o $(STD_STACK)

run_vector :
	@echo "$(GREEN)================================VECTOR=TEST========================================$(RESET)";	\
	./$(FT_VECTOR) > v_1;
	@ ./$(STD_VECTOR) > v_2;
	@diff -u --color=auto v_1 v_2; [ $$? -eq 1 ]

run_map:
	@echo "$(WARNING)================================MAP=TEST===========================================$(RESET)";	\
	./$(FT_MAP) > v_1;		\
	./$(STD_MAP) > v_2;		\
	diff -u --color=auto v_1 v_2; [ $$? -eq 1 ]

run_stack:
	@echo "$(OKCYAN)================================STACK=TEST=========================================$(RESET)";	\
	./$(FT_STACK) > v_1;		\
	./$(STD_STACK) > v_2;		\
	diff -u --color=auto v_1 v_2; [ $$? -eq 1 ]


test: run_vector run_map run_stack

clean:
	@$(RM) $(OBJ)
	@echo "$(FAIL)Delete object files.$(RESET)";

fclean: clean
	@$(RM) $(FT_VECTOR)
	@$(RM) $(STD_VECTOR)
	@$(RM) $(FT_MAP)
	@$(RM) $(STD_MAP)
	@$(RM) $(FT_STACK)
	@$(RM) $(STD_STACK)

	@$(RM) v_1
	@$(RM) v_2
	@echo "$(FAIL)Delete binary files.$(RESET)"

re: fclean all

.PHONY: re fclean clean run_vector run_map run_stack test all
