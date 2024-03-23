.PHONY: all clean

all: P1 P2 P3

clean:
	rm -f R1.txt R2.txt R3.txt Results.txt

P1: P1.c
	gcc P1.c -o P1  

P2: P2.c
	gcc P2.c -o P2

P3: P3.c
	gcc P3.c -o P3

run: all clean
	./P1 &
	./P2 &
	./P3 &
	rm -f P1 P2 P3
