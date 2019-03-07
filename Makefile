##
## EPITECH PROJECT, 2018
## Project Makefile
## File description:
## Build Makefile.
##

CC				=	g++

CXXFLAGS		=	-std=c++11 -Wall -Wextra -shared -fPIC

SRC				=	core/main.cpp

OBJ				=	$(SRC:.cpp=.o)

NAME			=	arcade

MAKE_SFMLAPI	=	make -C./lib/SFML

MAKE_GAMES	=	make -C./games

all: graphicals games $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)

graphicals:
	$(MAKE_SFMLAPI)

games:
	$(MAKE_GAMES)

clean:
	$(MAKE_SFMLAPI) clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE_SFMLAPI) fclean
	rm -f $(NAME)

re: fclean all
