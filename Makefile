##
## EPITECH PROJECT, 2018
## Project Makefile
## File description:
## Build Makefile.
##

NAME			=	arcade

MAKE_CORE		=	make -C./core

MAKE_NIBBLER	=	make -C./games/nibbler

MAKE_SFMLAPI	=	make -C./lib/SFML
MAKE_NCURSESAPI	=	make -C./lib/ncurses

MAKE_QTAPI		=	cd ./lib/Qt && cmake . && make && cd -
MAKE_QTAPI_MAC	=	cd ./lib/Qt && cmake -DCMAKE_PREFIX_PATH=/Users/$(USER)/Qt/5.12.2/clang_64/lib/cmake . && make && cd -

CLEAN_QTAPI		=	cd ./lib/Qt && rm -rf arcade-qt_autogen ; rm -rf CMakeFiles ; rm -rf cmake_install.cmake ; rm -rf CMakeCache.txt ; rm -rf Makefile
FCLEAN_QTAPI	=	cd ./lib/Qt && rm -rf arcade-qt_autogen ; rm -rf CMakeFiles ; rm -rf cmake_install.cmake ; rm -rf CMakeCache.txt ; rm -rf Makefile ; rm -rf ../lib_arcade_qt.so

all:
	$(MAKE_NIBBLER)
	$(MAKE_SFMLAPI)
	$(MAKE_NCURSESAPI)
	$(MAKE_CORE)
	$(MAKE_QTAPI)

mac:
	$(MAKE_NIBBLER) mac
	$(MAKE_SFMLAPI)
	$(MAKE_NCURSESAPI)
	$(MAKE_CORE) mac
	$(MAKE_QTAPI_MAC)

graphicals:
	$(MAKE_SFMLAPI)
	$(MAKE_NCURSESAPI)
	$(MAKE_QTAPI)

game:
	$(MAKE_NIBBLER)


clean:
	$(MAKE_CORE) clean
	$(MAKE_SFMLAPI) clean
	$(MAKE_NCURSESAPI) clean
	$(MAKE_NIBBLER) clean
	$(CLEAN_QTAPI)

fclean: clean
	$(MAKE_CORE) fclean
	$(MAKE_SFMLAPI) fclean
	$(MAKE_NCURSESAPI) fclean
	$(MAKE_NIBBLER) fclean
	$(FCLEAN_QTAPI)

re: fclean all
