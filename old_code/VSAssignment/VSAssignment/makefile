CC=gcc
CFLAGS=-c -Wall -gdwarf-2
DEPS = captcha.h metrics.h preprocessors.h readers.h utilites.h
UTILS = hellomake.h
READERS = readers.h
PREPROCESSORS = preprocessors.h
METRICS = metrics.h

OBJ = bounding_box.o copy_pixels.o crack_digit.o metrics.o print_image.o read_pbm.o utilities.o stack.o

all: crack

crack: $(OBJ)
	$(CC) $(OBJ) -o crack

bounding_box.o: bounding_box.c
	$(CC) $(CFLAGS) bounding_box.c

copy_pixels.o: copy_pixels.c
	$(CC) $(CFLAGS) copy_pixels.c

crack_digit.o: crack_digit.c
	$(CC) $(CFLAGS) crack_digit.c

metrics.o: metrics.c
	$(CC) $(CFLAGS) metrics.c

print_image.o: print_image.c
	$(CC) $(CFLAGS) print_image.c

read_pbm.o: read_pbm.c
	$(CC) $(CFLAGS) read_pbm.c

utilities.o: utilities.c
	$(CC) $(CFLAGS) utilities.c

stack.o: stack.c
	$(CC) $(CFLAGS) stack.c



clean:
	rm *o $(OBJ)