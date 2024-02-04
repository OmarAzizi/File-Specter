CC = gcc

# LIBNOTIFY_THINGY is required in order to not get it working with gcc.
# If you dont include it you will most likely get the following error the error (even if glib.h exist in your system):
# 
# fatal error: glib.h: No such file or directory
#      | #include <glib.h>
#      |          ^~~~~~~~
# compilation terminated.

LIBNOTIFY_THINGY = `pkg-config --cflags --libs libnotify` 

# if you are making a daemon you should put  'd' at the end of the name
filespecter: filespecter.o main.o
	$(CC) filespecter.o main.o -o filespecterd $(LIBNOTIFY_THINGY) 

filespecter.o: file_specter.c
	$(CC) -c file_specter.c -o filespecter.o $(LIBNOTIFY_THINGY)

main.o: main.c
	$(CC) -c main.c -o main.o $(LIBNOTIFY_THINGY)

clean:
	rm -f filespecter filespecter.o main.o

