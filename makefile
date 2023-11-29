all: main.exe

main.exe: main.o temp_functions.o
	gcc -o main temp_functions.o main.o

main.o: main.c
	gcc -c -o main.o main.c

temp_functions.o: temp_functions.c
	gcc -c -o temp_functions.o temp_functions.c

clean:
	rm *.o
	rm main.exe