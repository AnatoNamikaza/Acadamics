.PHONY: all clean

all: P1 P2 P3

clean:
	rm -f Sum_of_5s.txt Sub_of_3s.txt Div_of_2s.txt

P1: P1.c
	gcc -o P1 P1.c -pthread

P2: P2.c
	gcc -o P2 P2.c -pthread

P3: P3.c
	gcc -o P3 P3.c -pthread

run: clean all
	./P1
	./P2
	./P3
	rm -f P1 P2 P3
