CC = /usr/bin/gcc
CFLAGS = -Wall -g -O2 -Werror
CODE = chapter1.c
EXECUTABLE = chapter1

chapter1:
	$(CC) $(CFLAGS) $(CODE) -o $(EXECUTABLE)

run:
	./chapter1

clean:
	rm -rf $(EXECUTABLE)

.PHONY:
	clean chapter1 all
