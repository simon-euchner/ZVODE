# ---------------------------------------------------------------------------- #
#                                                                              #
# LICENSE NOTICE.                                                              #
#                                                                              #
#     LICENSES: GPL-3.0                                                        #
#                                                                              #
#     IMPORTANT: THIS IS FREE SOFTWARE WITHOUT ANY WARRANTY. THE USER IS IF    #
#                FREE TO MODIFY AND REDISTRIBUTE THIS SOFTWARE UNDER THE TERMS #
#                OF THE LICENSE LISTED ABOVE PUBLISHED BY THE FREE SOFTWARE    #
#                FOUNDATION. THE PUBLISHER, SIMON EUCHNER, IS NOT RESPONSIBLE  #
#                FOR ANY NEGATIVE EFFECTS THIS SOFTWARE MAY CAUSE.             #
#                                                                              #
# ---------------------------------------------------------------------------- #
#                                                                              #
# Makefile for C language interface to netlib's ZVODE ODE integrator           #
#                                                                              #
# ---------------------------------------------------------------------------- #


### Variables

# Compiler and Linker (GNU FORTRAN compiler/linker)
FC = gfortran
LD = gfortran
FLAGS = -Wall -pedantic -fcheck=all -ffixed-form
OLVL = -O1

# Paths
SRC = ./isr.d
OBJ = ./obj.d
BIN = ./bin.d
LSO = ./lib.d
CIF = ./cif.d

# LAPACK and BLAS
LIB = -llapack -lblas

# Target (binary *calendar*)
TARGET = ${LSO}/libzvode.so

# Define file names
F1  = zvode
F2  = zgbfa
F3  = zgbsl
F4  = zgefa
F5  = zgesl
F6  = zvodeC

# Specify object code files
OBJ_FILENAMES = ${F1}.o ${F2}.o ${F3}.o ${F4}.o ${F5}.o ${F6}.o
OBJ_FILES = ${foreach file, ${OBJ_FILENAMES}, ${OBJ}/${file}}


### Print info
all: ${TARGET}
	@echo -e "\nBuilding process completed successfully\n\n\n"


### Link
${TARGET}: ${OBJ_FILES}
	${LD} ${OLVL} -shared -o ${TARGET} ${wildcard ${OBJ}/*.o} ${LIB}


### Compile

# zvode.f
${OBJ}/${F1}.o: ${SRC}/${F1}.f
	${FC} ${FLAGS} -fPIC ${OLVL} -o ${OBJ}/${F1}.o -c ${SRC}/${F1}.f

# zgbfa.f
${OBJ}/${F2}.o: ${SRC}/${F2}.f
	${FC} ${FLAGS} -fPIC ${OLVL} -o ${OBJ}/${F2}.o -c ${SRC}/${F2}.f

# zgesl.f
${OBJ}/${F3}.o: ${SRC}/${F3}.f
	${FC} ${FLAGS} -fPIC ${OLVL} -o ${OBJ}/${F3}.o -c ${SRC}/${F3}.f

# zgefa.f
${OBJ}/${F4}.o: ${SRC}/${F4}.f
	${FC} ${FLAGS} -fPIC ${OLVL} -o ${OBJ}/${F4}.o -c ${SRC}/${F4}.f

# zgesl.f
${OBJ}/${F5}.o: ${SRC}/${F5}.f
	${FC} ${FLAGS} -fPIC ${OLVL} -o ${OBJ}/${F5}.o -c ${SRC}/${F5}.f

# zvodeC.c
${OBJ}/${F6}.o: ${CIF}/${F6}.c
	gcc -pedantic -Wall -Wextra -std=c99 -O1 -o ${OBJ}/${F6}.o -c ${CIF}/${F6}.c


### Cleanup

clean:
	rm ${OBJ}/*.o
	rm ${LSO}/*.so

.PHONY: clean
