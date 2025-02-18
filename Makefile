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
		$(FOLDER)strcasecmp.asm	\
		$(FOLDER)strstr.asm	\
		$(FOLDER)strpbrk.asm	\
		$(FOLDER)strcspn.asm	\

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

main: $(NAME)
	export LD_LIBRARY_PATH=$(shell pwd)
	gcc -no-pie tmain.c -L. -lasm -fno-builtin -o testmain
	LD_LIBRARY_PATH=$(shell pwd)/ LD_PRELOAD=$(shell pwd)/$(NAME) ./testmain

clean:
	rm -f $(OBJ) main.o test

fclean: clean
	rm -f $(NAME)

NAME_TEST = unit_tests

TEST_DIR = tests

FLAGS_TEST = --coverage -lcriterion

SRC_TESTS = \
	$(TEST_DIR)/strlen.c	\
	$(TEST_DIR)/strchr.c	\
	$(TEST_DIR)/strrchr.c	\
	$(TEST_DIR)/memset.c	\
	#$(TEST_DIR)/strcmp.c	\
	$(TEST_DIR)/memcpy.c	\
	$(TEST_DIR)/memmove.c	\
	$(TEST_DIR)/strncmp.c	\
	$(TEST_DIR)/strcasecmp.c	\
	$(TEST_DIR)/strpbrk.c	\
	$(TEST_DIR)/strcspn.c	\

unit_tests: re
	$(CC) -o $(NAME_TEST) $(SRC_TESTS) $(CFLAGS) $(FLAGS_TEST)

tests_run: $(NAME_TEST)
	rm -f *.gc*
	./$(NAME_TEST)
re: clean all

re: clean all
