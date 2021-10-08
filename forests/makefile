objects = forests.o alloc.o input_output.o iter.o nodes.o tests.o

.PHONY: all clean

all: forests

forests: $(objects)
	gcc -o $@ $(objects)

forests.o: forests.c alloc.h iter.h nodes.h input_output.h tests.h structs.h
	gcc -Wall -Wextra -c -std=c11 -O2 forests.c

nodes.o: nodes.c nodes.h structs.h tests.h alloc.h
	gcc -Wall -Wextra -c -std=c11 -O2 nodes.c

iter.o: iter.c iter.h structs.h tests.h
	gcc -Wall -Wextra -c -std=c11 -O2 iter.c

input_output.o: input_output.c input_output.h structs.h tests.h
	gcc -Wall -Wextra -c -std=c11 -O2 input_output.c

tests.o: tests.c tests.h structs.h
	gcc -Wall -Wextra -c -std=c11 -O2 tests.c

alloc.o: alloc.c alloc.h structs.h
	gcc -Wall -Wextra -c -std=c11 -O2 alloc.c

clean:
	-rm -f forests $(objects)