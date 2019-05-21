CFLAGS := -g
INCLUDE := -I ~/include
LDFLAGS := -L ~/lib -lsense -lm
%.o: %.c
	cc -c $(CFLAGS) $< $(INCLUDE)

gyro: gyro.o
	cc -o gyro $(INCLUDE) gyro.o $(LDFLAGS)

clean:
	rm -f *.o gyro
