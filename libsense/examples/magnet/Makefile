CFLAGS := -g
INCLUDE := -I ~/include
LDFLAGS := -L ~/lib -lsense
%.o: %.c
	cc -c $(CFLAGS) $< $(INCLUDE)

magnet: magnet.o
	cc -o magnet $(INCLUDE) magnet.o $(LDFLAGS)

clean:
	rm -f *.o magnet
