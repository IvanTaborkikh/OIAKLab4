all: lab4_O0 lab4_O1 lab4_O2 lab4_O3 lab4_Os

lab4_O0: src/main.c src/timer.c src/data_gen.c src/arith_c.c src/arith_asm.c
	gcc -std=c11 -O0 -DOPT_LABEL=\"O0\" -Iinclude src/main.c src/timer.c src/data_gen.c src/arith_c.c src/arith_asm.c -o lab4_O0

lab4_O1: src/main.c src/timer.c src/data_gen.c src/arith_c.c src/arith_asm.c
	gcc -std=c11 -O -DOPT_LABEL=\"O1\" -Iinclude src/main.c src/timer.c src/data_gen.c src/arith_c.c src/arith_asm.c -o lab4_O1

lab4_O2: src/main.c src/timer.c src/data_gen.c src/arith_c.c src/arith_asm.c
	gcc -std=c11 -O2 -DOPT_LABEL=\"O2\" -Iinclude src/main.c src/timer.c src/data_gen.c src/arith_c.c src/arith_asm.c -o lab4_O2

lab4_O3: src/main.c src/timer.c src/data_gen.c src/arith_c.c src/arith_asm.c
	gcc -std=c11 -O3 -DOPT_LABEL=\"O3\" -Iinclude src/main.c src/timer.c src/data_gen.c src/arith_c.c src/arith_asm.c -o lab4_O3

lab4_Os: src/main.c src/timer.c src/data_gen.c src/arith_c.c src/arith_asm.c
	gcc -std=c11 -Os -DOPT_LABEL=\"Os\" -Iinclude src/main.c src/timer.c src/data_gen.c src/arith_c.c src/arith_asm.c -o lab4_Os

clean:
	rm lab4_O0 lab4_O1 lab4_O2 lab4_O3 lab4_Os
