CFLAGS := -g
INCLUDE := -I ~/include
LDFLAGS := -L ~/lib -lsense
%.o: %.c
	cc -c $(CFLAGS) $< $(INCLUDE)

clicker: clicker.o
	cc -o clicker $(INCLUDE) clicker.o $(LDFLAGS)

clean:
	rm -f *.o clicker
