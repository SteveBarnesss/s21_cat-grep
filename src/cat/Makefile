SHELL := /bin/bash
FLAGS = -Wall -Werror -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L -D_XOPEN_SOURCE=700
FILE = *.txt

all: s21_cat tests

s21_cat: 
	gcc $(FLAGS) s21_cat.c -o s21_cat

tests:
	-diff <(./s21_cat $(FILE)) <(cat $(FILE))
	-diff <(./s21_cat -e $(FILE)) <(cat -e $(FILE))
	-diff <(./s21_cat -t $(FILE)) <(cat -t $(FILE))
	-diff <(./s21_cat -n $(FILE)) <(cat -n $(FILE))
	-diff <(./s21_cat -b $(FILE)) <(cat -b $(FILE))
	-diff <(./s21_cat -s $(FILE)) <(cat -s $(FILE))
	-diff <(./s21_cat --number $(FILE)) <(cat -n $(FILE))
	-diff <(./s21_cat --number-nonblank $(FILE)) <(cat -b $(FILE))
	-diff <(./s21_cat --squeeze-blank $(FILE)) <(cat -s $(FILE))
	-diff <(./s21_cat -etnbs $(FILE)) <(cat -etnbs $(FILE))
	-diff <(./s21_cat -vT $(FILE)) <(cat -t $(FILE))
	-diff <(./s21_cat -v -b -s -t $(FILE)) <(cat -v -b -s -t $(FILE))
	-diff <(./s21_cat -s -b -v -t $(FILE)) <(cat -s -b -v -t $(FILE))

clean:
	rm -f s21_cat

.PHONY: all clean tests