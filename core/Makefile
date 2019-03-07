##
## EPITECH PROJECT, 2018
## Project Makefile
## File description:
## Build Makefile.
##

CXX				=	g++

CXXFLAGS		=	-std=c++11 -Wall -Wextra -W -ldl

SRC				=	main.cpp

OBJ				=	$(SRC:.cpp=.o)

NAME			=	arcade

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)
	mv $(NAME) ..

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ../$(NAME)

re: fclean all
