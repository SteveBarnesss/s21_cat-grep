SHELL := /bin/bash
FLAGS = -Wall -Werror -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L -D_XOPEN_SOURCE=700
FILE = test1.txt test2.txt test3.txt
PATTERN = pattern.txt
FILE1 = test1.txt

all: s21_grep tests check

s21_grep: 
	gcc $(FLAGS) s21_grep.c -o s21_grep

tests:
	 #TEST1 SOLO FLAGS===============================================================
	-diff <(./s21_grep -e sha $(FILE1)) <(grep -e sha $(FILE1))
	-diff <(./s21_grep -e sha $(FILE)) <(grep -e sha $(FILE))
	-diff <(./s21_grep -l flagl $(FILE)) <(grep -l flagl $(FILE))
	-diff <(./s21_grep -i sha $(FILE)) <(grep -i sha $(FILE))
	-diff <(./s21_grep -v match $(FILE)) <(grep -v match $(FILE))
	-diff <(./s21_grep -c match $(FILE)) <(grep -c match $(FILE))
	-diff <(./s21_grep -n match $(FILE)) <(grep -n match $(FILE))
	-diff <(./s21_grep -h flagl $(FILE)) <(grep -h flagl $(FILE))
	-diff <(./s21_grep -s sha un.txt $(FILE)) <(grep -s sha un.txt $(FILE))
	-diff <(./s21_grep -e sha -e sha -e match $(FILE)) <(grep -e sha -e sha -e match $(FILE))
	-diff <(./s21_grep -f empty_pattern.txt $(FILE)) <(grep -f empty_pattern.txt $(FILE))
	-diff <(./s21_grep -f $(PATTERN) $(FILE)) <(grep -f $(PATTERN) $(FILE))
	-diff <(./s21_grep -o only $(FILE)) <(grep -o only $(FILE))

	#TEST2 BASIC COMBINES============================================================
	-diff <(./s21_grep -i -v sha $(FILE)) <(grep -i -v sha $(FILE))
	-diff <(./s21_grep -i -n sha $(FILE)) <(grep -i -n sha $(FILE))
	-diff <(./s21_grep -i -c sha $(FILE)) <(grep -i -c sha $(FILE))
	-diff <(./s21_grep -v -n match $(FILE)) <(grep -v -n match $(FILE))
	-diff <(./s21_grep -v -c match $(FILE)) <(grep -v -c match $(FILE))
	-diff <(./s21_grep -n -h match $(FILE)) <(grep -n -h match $(FILE))
	-diff <(./s21_grep -e sha -i $(FILE)) <(grep -e sha -i $(FILE))
	-diff <(./s21_grep -e sha -v $(FILE)) <(grep -e sha -v $(FILE))
	-diff <(./s21_grep -e sha -c $(FILE)) <(grep -e sha -c $(FILE))
	-diff <(./s21_grep -e sha -n $(FILE)) <(grep -e sha -n $(FILE))
	-diff <(./s21_grep -f $(PATTERN) -i $(FILE)) <(grep -f $(PATTERN) -i $(FILE))
	-diff <(./s21_grep -f $(PATTERN) -v $(FILE)) <(grep -f $(PATTERN) -v $(FILE))
	-diff <(./s21_grep -f $(PATTERN) -c $(FILE)) <(grep -f $(PATTERN) -c $(FILE))
	-diff <(./s21_grep -f $(PATTERN) -n $(FILE)) <(grep -f $(PATTERN) -n $(FILE))
	-diff <(./s21_grep -o -i only $(FILE)) <(grep -o -i only $(FILE))
	-diff <(./s21_grep -o -n only $(FILE)) <(grep -o -n only $(FILE))
	-diff <(./s21_grep -l -h match $(FILE)) <(grep -l -h match $(FILE))

	#TEST3 TRIPLE COMBINES==========================================================
	-diff <(./s21_grep -i -v -n sha $(FILE)) <(grep -i -v -n sha $(FILE))
	-diff <(./s21_grep -i -v -c sha $(FILE)) <(grep -i -v -c sha $(FILE))
	-diff <(./s21_grep -i -n -c sha $(FILE)) <(grep -i -n -c sha $(FILE))
	-diff <(./s21_grep -v -n -c match $(FILE)) <(grep -v -n -c match $(FILE))
	-diff <(./s21_grep -e sha -i -v $(FILE)) <(grep -e sha -i -v $(FILE))
	-diff <(./s21_grep -e sha -i -n $(FILE)) <(grep -e sha -i -n $(FILE))
	-diff <(./s21_grep -e sha -i -c $(FILE)) <(grep -e sha -i -c $(FILE))
	-diff <(./s21_grep -e sha -v -n $(FILE)) <(grep -e sha -v -n $(FILE))
	-diff <(./s21_grep -e sha -v -c $(FILE)) <(grep -e sha -v -c $(FILE))
	-diff <(./s21_grep -f $(PATTERN) -i -v $(FILE)) <(grep -f $(PATTERN) -i -v $(FILE))
	-diff <(./s21_grep -f $(PATTERN) -i -n $(FILE)) <(grep -f $(PATTERN) -i -n $(FILE))
	-diff <(./s21_grep -f $(PATTERN) -v -c $(FILE)) <(grep -f $(PATTERN) -v -c $(FILE))
	-diff <(./s21_grep -i -n -h sha $(FILE)) <(grep -i -n -h sha $(FILE))
	-diff <(./s21_grep -o -i -n only test1.txt) <(grep -o -i -n only test1.txt)
			
	#TEST4 QUAD+ COMBINES===========================================================
	-diff <(./s21_grep -i -v -c -n sha test1.txt) <(grep -i -v -c -n sha test1.txt)
	-diff <(./s21_grep -e sha -i -v -n test1.txt) <(grep -e sha -i -v -n test1.txt)
	-diff <(./s21_grep -e sha -i -v -c test1.txt) <(grep -e sha -i -v -c test1.txt)
	-diff <(./s21_grep -f $(PATTERN) -i -v -n test1.txt) <(grep -f $(PATTERN) -i -v -n test1.txt)
	-diff <(./s21_grep -f $(PATTERN) -i -v -c test1.txt) <(grep -f $(PATTERN) -i -v -c test1.txt)
	-diff <(./s21_grep -i -v -n -h sha $(FILE)) <(grep -i -v -n -h sha $(FILE))
	-diff <(./s21_grep -e sha -e match -i -v test1.txt) <(grep -e sha -e match -i -v test1.txt)
	-diff <(./s21_grep -e sha -f $(PATTERN) -i -n test1.txt) <(grep -e sha -f $(PATTERN) -i -n test1.txt)
	
	#TEST5 EDGE CASES===============================================================
	-diff <(./s21_grep -v -v sha test1.txt) <(grep -v -v sha test1.txt)
	-diff <(./s21_grep -i -i sha test1.txt) <(grep -i -i sha test1.txt)
	-diff <(./s21_grep -c -c match test1.txt) <(grep -c -c match test1.txt)
	-diff <(./s21_grep -n -n match test1.txt) <(grep -n -n match test1.txt)
	-diff <(./s21_grep sha $(FILE)) <(grep sha $(FILE))
	-diff <(./s21_grep -s sha nonexist1.txt nonexist2.txt 2>&1) <(grep -s sha nonexist1.txt nonexist2.txt 2>&1)
	#All tests completed============================================================
#check:
	#leaks -atExit -- ./s21_grep -e sha test1.txt
	#leaks -atExit -- ./s21_grep -e sha -e he -e match test1.txt
	#leaks -atExit -- ./s21_grep -f nofile.txt test1.txt
	#leaks -atExit -- ./s21_grep sha test1.txt
	#leaks -atExit -- ./s21_grep "[]" test1.txt

clean:
	rm -f s21_grep

.PHONY: all clean