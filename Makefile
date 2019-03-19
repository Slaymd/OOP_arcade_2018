##
## EPITECH PROJECT, 2018
## Project Makefile
## File description:
## Build Makefile.
##

NAME			=	arcade

MAKE_CORE		=	make -C./core

MAKE_GAME		=	make -C./games/nibbler

MAKE_SFMLAPI	=	make -C./lib/SFML

all:
	$(MAKE_SFMLAPI)
	$(MAKE_CORE)
	$(MAKE_GAME)

core:
	$(MAKE_CORE)

game:
	$(MAKE_GAME)

graphicals:
	$(MAKE_SFMLAPI)

clean:
	$(MAKE_CORE) clean
	$(MAKE_SFMLAPI) clean
	$(MAKE_GAMES) clean

fclean: clean
	$(MAKE_CORE) fclean
	$(MAKE_SFMLAPI) fclean
	$(MAKE_GAMES) fclean

re: fclean all
