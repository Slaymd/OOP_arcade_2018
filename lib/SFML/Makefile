##
## EPITECH PROJECT, 2018
## Project Makefile
## File description:
## Build Makefile.
##

CXX		=	g++

CXXFLAGS=	-std=c++11 -Wall -Wextra -shared -fPIC

SRC		=	SFMLGraphAPI.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME	=	lib_arcade_sfml.so

all: $(NAME)

$(NAME):
	$(CXX) $(CXXFLAGS) -o $(NAME) $(SRC)
	mv $(NAME) ..

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ../$(NAME)

re: fclean all