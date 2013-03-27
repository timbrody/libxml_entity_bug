

CFLAGS=`xml2-config --cflags`
LIBS=`xml2-config --libs`

OBJECTS=main.o

all: main
main: $(OBJECTS)
	$(CC) -o main $(OBJECTS) $(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

test: main
	./main test.xml .
