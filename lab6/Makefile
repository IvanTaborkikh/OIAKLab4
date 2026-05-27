all: lab6_O0

lab6_O0: src/main.c src/timer.c src/data_gen.c src/poly.c
	gcc -std=c11 -O0 -DOPT_LABEL=\"O0\" -Iinclude \
	    src/main.c src/timer.c src/data_gen.c src/poly.c \
	    -o lab6_O0

clean:
	rm -f lab6_O0s