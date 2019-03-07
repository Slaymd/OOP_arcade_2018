##
## EPITECH PROJECT, 2018
## Project Makefile
## File description:
## Build Makefile.
##

CXX		=	g++

CXXFLAGS=	-std=c++11 -Wall -Wextra -shared -fPIC

SFML	=	-lsfml-graphics -lsfml-system -lsfml-audio -lsfml-window

SRC		=	SFMLGraphAPI.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME	=	lib_arcade_sfml.so

all: $(NAME)

$(NAME):
	$(CXX) $(CXXFLAGS) $(SFML) -o $(NAME) $(SRC)
	mv $(NAME) ..

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ../$(NAME)

re: fclean all