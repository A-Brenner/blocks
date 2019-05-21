CFLAGS := -g
INCLUDE := -I ~/include
LDFLAGS := -L ~/lib -lsense

%.o: %.c
all:
	cc -c input.c output.c main.c $< $(INCLUDE)
	cc -o block $(INCLUDE) input.o output.o main.o $(LDFLAGS)

outputtest:
	cc -c output.c outputtest.c $< $(INCLUDE)
	cc -o outtest $(INCLUDE)  outputtest.o framebuffer.o output.o $(LDFLAGS)

inputtest:
	cc -c input.c inputtest.c $< $(INCLUDE)
	cc -o intest $(INCLUDE) inputtest.o framebuffer.o input.o $(LDFLAGS)

clean:
	rm -v -f input.o main.o output.o inputtest.o outputtest.o outtest intest block
