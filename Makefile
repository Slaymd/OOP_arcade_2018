##
## EPITECH PROJECT, 2018
## Project Makefile
## File description:
## Build Makefile.
##

MAC			=	mac

CORE		=	core

GAMES		=	games

GRAPHICALS	=	graphicals

all: $(CORE) $(GAMES) $(GRAPHICALS)

$(MAC):
	make -C./games/nibbler mac
	make -C./games/solarfox mac
	make -C./lib/SFML
	make -C./lib/ncurses
	make -C./core mac
	cd ./lib/Qt && cmake -DCMAKE_PREFIX_PATH=/Users/$(USER)/Qt/5.12.2/clang_64/lib/cmake . && make && cd -

$(CORE): make_core

$(GAMES): make_games

$(GRAPHICALS): make_graphicals

make_core:
	make -C./core

make_games:
	make -C./games/nibbler
	make -C./games/solarfox

make_graphicals:
	make -C./lib/ncurses
	make -C./lib/SFML
	cd ./lib/Qt && cmake . && make && cd -

clean:
	make -C./games/nibbler clean
	make -C./games/solarfox clean
	make -C./lib/SFML clean
	make -C./lib/ncurses clean
	make -C./core clean
	cd ./lib/Qt && rm -rf arcade-qt_autogen ; rm -rf CMakeFiles ; rm -rf cmake_install.cmake ; rm -rf CMakeCache.txt ; rm -rf Makefile

fclean: clean
	make -C./games/nibbler fclean
	make -C./games/solarfox fclean
	make -C./lib/SFML fclean
	make -C./lib/ncurses fclean
	make -C./core fclean
	cd ./lib/Qt && rm -rf arcade-qt_autogen ; rm -rf CMakeFiles ; rm -rf cmake_install.cmake ; rm -rf CMakeCache.txt ; rm -rf Makefile ; rm -rf ../lib_arcade_qt.so

re: fclean all