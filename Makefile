MACROS = -Wall

all: main.o dfa.o table.o bin
	gcc main.o dfa.o table.o -o bin/main.exe

bin:
	mkdir -p bin

table.o: table.c
	gcc -c $(MACROS) table.c
main.o: main.c 
	gcc -c $(MACROS) main.c
dfa.o: dfa.c
	gcc -c $(MACROS) dfa.c

clean:
	rm -rf *.o bin/
