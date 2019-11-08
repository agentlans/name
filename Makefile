# Makefile adapted from https://stackoverflow.com/a/2481307

name: main.cpp
	c++ -o name main.cpp

all: name ;

clean:
	rm -f name

