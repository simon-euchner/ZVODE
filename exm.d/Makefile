# ---------------------------------------------------------------------------- #
#                                                                              #
# This file is part of the C language interface to ZVODE by Simon Euchner.     #
#                                                                              #
# ---------------------------------------------------------------------------- #
#                                                                              #
# LICENSE NOTICE.                                                              #
#                                                                              #
#     LICENSES: GPL-3.0                                                        #
#                                                                              #
#     IMPORTANT: THIS IS FREE SOFTWARE WITHOUT ANY WARRANTY. THE USER IS FREE  #
#                TO MODIFY AND REDISTRIBUTE THIS SOFTWARE UNDER THE TERMS OF   #
#                THE LICENSE LISTED ABOVE PUBLISHED BY THE FREE SOFTWARE       #
#                FOUNDATION. THE PUBLISHER, SIMON EUCHNER, IS NOT RESPONSIBLE  #
#                FOR ANY NEGATIVE EFFECTS THIS SOFTWARE MAY CAUSE.             #
#                                                                              #
# ---------------------------------------------------------------------------- #
#                                                                              #
# Makefile for example usage of C language interface                           #
#                                                                              #
# ---------------------------------------------------------------------------- #


### Variables
CC = gcc
FLAGS = -pedantic -Wall -Wextra -std=c99 -O1
LIB = -lzvode

all: ../bin.d/example.out
	@echo -e "\nBuilding process completed successfully"
	@echo -e "\nRunning now *../bin.d/example.out*\n\n\n"
	@LD_LIBRARY_PATH=../lib.d/ ../bin.d/example.out

### Link
../bin.d/example.out: ../obj.d/example.o
	${CC} ${FLAGS} -L../lib.d  ../obj.d/example.o -o ../bin.d/example.out ${LIB}

### Compile
../obj.d/example.o: ./example.c
	${CC} ${FLAGS} -c ./example.c -o ../obj.d/example.o

### Cleanup
clean:
	rm ../bin.d/example.out
	rm ../obj.d/example.o
.PHONY: clean
