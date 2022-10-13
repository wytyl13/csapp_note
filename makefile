CC = /usr/bin/gcc
CFLAGS = -Wall -g -O2 -Werror
CODE1 = chapter1.c
CODE2 = chapter2.c
EXECUTABLE1 = chapter1
EXECUTABLE2 = chapter2

chapter1:
	$(CC) $(CFLAGS) $(CODE1) -o $(EXECUTABLE1)

chapter2:
	$(CC) $(CFLAGS) $(CODE2) -o $(EXECUTABLE2)

run_chaptrer1:
	./chapter1

run_chapter2:
	./chapter2

clean:
	rm -rf $(EXECUTABLE1) $(EXECUTABLE2)

.PHONY:
	clean chapter1 chapter2
