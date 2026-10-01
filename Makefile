CC = clang
CFLAGS = -Wall -Wextra -g -fPIC

liboml.so: src/liboml.c src/liboml.h
	$(CC) $(CFLAGS) -shared src/liboml.c -o $@

clean:
	rm -f liboml.so

.PHONY: clean
