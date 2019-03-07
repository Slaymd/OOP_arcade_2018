##
## EPITECH PROJECT, 2018
## Project Makefile
## File description:
## Build Makefile.
##

CXX				=	g++

CXXFLAGS		=	-std=c++11 -Wall -Wextra -W -ldl

SRC				=	core/main.cpp

OBJ				=	$(SRC:.cpp=.o)

NAME			=	arcade

MAKE_SFMLAPI	=	make -C./lib/SFML

all: core graphicals

core:
	$(CXX) $(CXXFLAGS) -o $(NAME) $(SRC)

graphicals:
	$(MAKE_SFMLAPI)

clean:
	$(MAKE_SFMLAPI) clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE_SFMLAPI) fclean
	rm -f $(NAME)

re: fclean all
