all: main

main: main.o complex.o sort_complex.o
	$(CC) $(CFLAGS) -o main main.o complex.o sort_complex.o

main.o: main.cpp complex.h sort_complex.h
	$(CC) $(CFLAGS) -c main.cpp

complex.o: complex.cpp complex.h
	$(CC) $(CFLAGS) -c complex.cpp

sort_complex.o: sort_complex.cpp sort_complex.h complex.h
	$(CC) $(CFLAGS) -c sort_complex.cpp

clean:
	rm -f *.o main
