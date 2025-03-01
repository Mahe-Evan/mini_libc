##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

NAME	=	libasm.so
BONUS_NAME	=	libasm_bonus.so

FOLDER	=	./minilibc/
BONUS	=	./bonus/

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
		$(FOLDER)index.asm	\
		$(FOLDER)rindex.asm	\

BONUS_SRC	=	$(BONUS)xstrlen.asm	\
			$(BONUS)xstrchr.asm	\
			$(BONUS)xstrrchr.asm	\
			$(BONUS)xmemset.asm	\
			$(BONUS)xmemcpy.asm	\
			$(BONUS)xstrcmp.asm	\
			$(BONUS)xstrncmp.asm	\
			$(BONUS)xmemmove.asm	\
			$(BONUS)xstrcasecmp.asm	\
			$(BONUS)xstrstr.asm	\
			$(BONUS)xstrpbrk.asm	\
			$(BONUS)xstrcspn.asm	\

OBJ	=	$(SRC:.asm=.o)
BONUS_OBJ	=	$(BONUS_SRC:.asm=.o)

NASM	=	nasm
CC	=	gcc

NASMFLAGS = -f elf64
LDFLAGS = -shared -o

all: $(NAME)

$(NAME): $(OBJ)
	ld $(LDFLAGS) $(NAME) $(OBJ)

bonus: $(BONUS_OBJ)
	ld $(LDFLAGS) $(BONUS_NAME) $(BONUS_OBJ)

%.o: %.asm
	$(NASM) $(NASMFLAGS) -o $@ $<

main: $(NAME)
	export LD_LIBRARY_PATH=$(shell pwd)
	gcc -no-pie tmain.c -L. -lasm -fno-builtin -o testmain
	LD_LIBRARY_PATH=$(shell pwd)/ LD_PRELOAD=$(shell pwd)/$(NAME) ./testmain

clean:
	rm -f $(OBJ) main.o test
	rm -f *.gcda
	rm -f *.gcno
	rm -f $(BONUS_OBJ)
	rm -f $(NAME_TEST)
	rm -f $(BONUS_TEST)

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)

NAME_TEST = unit_tests
BONUS_TEST = bonus_tests

TEST_DIR = tests

FLAGS_TEST = --coverage -lcriterion

TEST_DIR = tests

FLAGS_TEST = --coverage -lcriterion

SRC_TESTS = \
	$(TEST_DIR)/strlen.c	\
	$(TEST_DIR)/strchr.c	\
	$(TEST_DIR)/strrchr.c	\
	$(TEST_DIR)/memset.c	\
	$(TEST_DIR)/memcpy.c	\
	$(TEST_DIR)/strcmp.c	\
	$(TEST_DIR)/memmove.c	\
	$(TEST_DIR)/strncmp.c	\
	$(TEST_DIR)/strcasecmp.c	\
	$(TEST_DIR)/strpbrk.c	\
	$(TEST_DIR)/strcspn.c	\
	$(TEST_DIR)/strstr.c	\
	$(TEST_DIR)/index.c	\
	$(TEST_DIR)/rindex.c	\

unit_tests: re
	$(CC) -o $(NAME_TEST) $(SRC_TESTS) $(CFLAGS) $(FLAGS_TEST)

tests_run: $(NAME_TEST)
	rm -f *.gc*
	./$(NAME_TEST)

BONUS_TESTS = \
	$(TEST_DIR)/xstrlen.c	\
	$(TEST_DIR)/xstrchr.c	\
	$(TEST_DIR)/xstrrchr.c	\
	$(TEST_DIR)/xmemset.c	\
	$(TEST_DIR)/xmemcpy.c	\
	$(TEST_DIR)/xstrcmp.c	\
	$(TEST_DIR)/xmemmove.c	\
	$(TEST_DIR)/xstrncmp.c	\
	$(TEST_DIR)/xstrcasecmp.c	\
	$(TEST_DIR)/xstrpbrk.c	\
	$(TEST_DIR)/xstrcspn.c	\
	$(TEST_DIR)/xstrstr.c	\

bonus_tests: re
	$(CC) -o $(BONUS_TEST) $(BONUS_TESTS) $(CFLAGS) $(FLAGS_TEST)

bonus_run: $(BONUS_TEST)
	rm -f *.gc*
	./$(BONUS_TEST)

re: fclean clean all
