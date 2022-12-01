CC = /usr/bin/gcc
CFLAGS = -Wall -g -O2 -Werror
CODE1 = chapter1.c
CODE2 = chapter2.c
CODE3 = chapter3.c
CODE5 = chapter5.c
EXECUTABLE1 = chapter1
EXECUTABLE2 = chapter2
EXECUTABLE3 = chapter3
EXECUTABLE5 = chapter5

chapter1:
	$(CC) $(CFLAGS) $(CODE1) -o $(EXECUTABLE1)

chapter2:
	$(CC) $(CFLAGS) $(CODE2) -o $(EXECUTABLE2)

chapter3:
	$(CC) $(CFLAGS) $(CODE3) -o $(EXECUTABLE3)

chapter5:
	$(CC) $(CFLAGS) $(CODE5) -o $(EXECUTABLE5)

run_chaptrer1:
	./chapter1

run_chapter2:
	./chapter2

run_chapter3:
	./chapter3

run_chapter5:
	./chapter5

clean:
	rm -rf $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3)

.PHONY:
	clean chapter1 chapter2 chapter3
