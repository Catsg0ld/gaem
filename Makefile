gaem: main.c main.h Makefile
	cc main.c -L./raylib/lib -I./raylib/include -lraylib -lm -o gaem

clean:
	rm gaem