CC=gcc
INCLUDE=./include/*.h

CFLAGS=

SOURCES=$(wildcard src/*.c)
OBJECTS = $(patsubst src/%.c, objs/%.o, $(SOURCES))

all : build/main $(INCLUDE) 

run : all
	build/main

build/ :
	mkdir -p build objs

build/main : $(OBJECTS)
	$(CC) $^ -o $@

objs/%.o : src/%.c | build/
	$(CC) $(CFLAGS) -Iinclude -c  $< -o $@

clean:
	rm -rf build objs