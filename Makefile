# Made by (c) lenanya
# Refactored by (c) Catsgold 

src_files := $(wildcard src/*.c)
obj_files := $(src_files:.c=.o)

gaem: $(obj_files)
	cc $(obj_files) ./raylib/lib/libraylib.a -lm -Iinclude -I./raylib/include -o gaem

src/%.o: src/%.c
	cc -c $< -o $@ -Iinclude -I./raylib/include

clean:
	rm -f $(obj_files) gaem
