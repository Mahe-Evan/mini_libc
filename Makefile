##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

NAME	=	libasm.so

FOLDER	=	./minilibc/

SRC	=	$(FOLDER)strlen.asm	\
		$(FOLDER)strchr.asm	\
		$(FOLDER)strrchr.asm	\
		$(FOLDER)memset.asm	\
		$(FOLDER)memcpy.asm	\
		$(FOLDER)strcmp.asm	\
		$(FOLDER)strncmp.asm	\
		$(FOLDER)memmove.asm	\

OBJ	=	$(SRC:.asm=.o)

NASM	=	nasm
CC	=	gcc

NASMFLAGS = -f elf64
LDFLAGS = -shared -o

all: $(NAME)

$(NAME): $(OBJ)
	ld $(LDFLAGS) $(NAME) $(OBJ)

%.o: %.asm
	$(NASM) $(NASMFLAGS) -o $@ $<

clean:
	rm -f $(OBJ) main.o test

fclean: clean
	rm -f $(NAME)

# main: $(NAME)
# 	export LD_LIBRARY_PATH=$(shell pwd)
# 	gcc -no-pie tmain.c -L. -lasm -fno-builtin -o testmain
# 	LD_LIBRARY_PATH=$(shell pwd)/ LD_PRELOAD=$(shell pwd)/$(NAME) ./testmain

re: clean all
