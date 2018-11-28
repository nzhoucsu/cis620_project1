all: pcrt tcrt mm_bench

pcrt: crt.o ep.o et.o etime.o
	gcc crt.o ep.o et.o etime.o -o pcrt -lpthread
mm_bench: etime.o mm_thr.o
	gcc etime.o mm_thr.o -o mm_bench -lpthread
tcrt: pcrt
	ln pcrt tcrt

crt.o: crt.c
	gcc -c crt.c
ep.o: ep.c
	gcc -c ep.c
et.o: et.c
	gcc -c et.c
mm_thr.o: mm_thr.c
	gcc -c mm_thr.c	
etime.o: etime.c
	gcc -c etime.c


