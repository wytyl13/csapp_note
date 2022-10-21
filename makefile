CC = /usr/bin/gcc
CFLAGS = -Wall -g -O2 -Werror
CODE1 = chapter1.c
CODE2 = chapter2.c
CODE3 = chapter3.c
EXECUTABLE1 = chapter1
EXECUTABLE2 = chapter2
EXECUTABLE3 = chapter3

chapter1:
	$(CC) $(CFLAGS) $(CODE1) -o $(EXECUTABLE1)

chapter2:
	$(CC) $(CFLAGS) $(CODE2) -o $(EXECUTABLE2)

chapter2:
	$(CC) $(CFLAGS) $(CODE3) -o $(EXECUTABLE3)

run_chaptrer1:
	./chapter1

run_chapter2:
	./chapter2

run_chapter3:
	./chapter3

clean:
	rm -rf $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3)

.PHONY:
	clean chapter1 chapter2 chapter3
