##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

NAME	=	libasm.so

FOLDER	=	./minilibc/

SRC	=	$(FOLDER)strlen.asm

OBJ	=	$(SRC:.asm=.o)

NASM	=	nasm
CC	=	gcc

NASMFLAGS = -f elf64
LDFLAGS = -shared -o

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -nostdlib -shared -o $(NAME) -fPIC $(OBJ)

%.o: %.asm
	$(NASM) $(NASMFLAGS) -o $@ $<

clean:
	rm -f $(OBJ) main.o test

fclean: clean
	rm libasm.so

re: clean all
