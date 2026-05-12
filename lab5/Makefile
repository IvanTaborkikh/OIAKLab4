all: lab5

lab5: src/main.c src/timer.c src/data_gen.c src/arith_xmm.c
	gcc -std=c11 -O0 -Iinclude src/main.c src/timer.c src/data_gen.c src/arith_xmm.c -o lab5 -lm

clean:
	rm lab5
