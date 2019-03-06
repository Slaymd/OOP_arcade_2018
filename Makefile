##
## EPITECH PROJECT, 2018
## Project Makefile
## File description:
## Build Makefile.
##

CC		=	g++

CFLAGS	=	-Wall -Wextra -shared -fPIC

SRC		=	core/main.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME	=	arcade

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
