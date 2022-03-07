
CXX = clang++
SANFLAGS = -fsanitize=address
DEBUGFLAGS = -g -fno-limit-debug-info
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 $(DEBUGFLAGS) $(SANFLAGS) -O3

# =======================================VECTOR=SETTING==========================================================
VECTOR_SRC = \
	Vector.cpp	\

VECTOR_SRC := $(addprefix Vector/src/, $(VECTOR_SRC))

VECTOR_SRC += Vector/main.cpp

VECTOR_OBJ = $(VECTOR_SRC:.cpp=.o)

VECTOR_HPP = \
	Vector.hpp	\

VECTOR_HPP := $(addprefix Vector/head/, $(VECTOR_HPP))

VECTOR_DIR = ./Vector/head

VECTOR = vector

# =======================================Run===================================================================

all: $(VECTOR)
	./vector
# ================VECTOR==================
$(VECTOR_OBJ): %.o: %.cpp $(VECTOR_HPP)  Makefile
	$(CXX) $(CXXFLAGS) -c $< -I $(VECTOR_DIR) -o $@

$(VECTOR) : $(VECTOR_OBJ)
	$(CXX) $(VECTOR_OBJ) $(CXXFLAGS) -o $(VECTOR)