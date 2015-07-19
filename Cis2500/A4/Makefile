
# Flags that are sent to the compiler
# Do not change these
CFLAGS      =	-Wall -ansi -pedantic -g -Iinclude


music:
	gcc $(CFLAGS) src/main.c -o bin/music

test: 
	gcc $(CFLAGS) src/listTest.c src/linkedList.c -o bin/listTest

clean:
	@ rm *.o
