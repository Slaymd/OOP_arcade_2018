##
## EPITECH PROJECT, 2018
## Project Makefile
## File description:
## Build Makefile.
##

CXX		=	g++

CXXFLAGS=	-std=c++14 -Wall -Wextra -shared -fPIC -I../../core -I.. -I. -I../../lib -Wl,-undefined,dynamic_lookup

SRC		=	Menu.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME	=	lib_arcade_menu.so

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)
	mv $(NAME) ..

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ../$(NAME)

re: fclean all
