##
## EPITECH PROJECT, 2018
## Project Makefile
## File description:
## Build Makefile.
##

CXX			=	g++

CXXFLAGS	=	-std=c++11 -Wall -Wextra -W -I. -I../games -I../lib

SRC			=	main.cpp    \
                Engine.cpp

OBJ			=	$(SRC:.cpp=.o)

NAME		=	arcade

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) -ldl -Wl,-E
	mv $(NAME) ..

mac: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) -ldl -Wl,-undefined,dynamic_lookup
	mv $(NAME) ..

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ../$(NAME)

re: fclean all
