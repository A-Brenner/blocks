CFLAGS := -g
INCLUDE := -I ~/include
LDFLAGS := -L ~/lib -lsense
%.o: %.c
	cc -c $(CFLAGS) $< $(INCLUDE)

weather: weather.o
	cc -o weather $(INCLUDE) weather.o $(LDFLAGS)

clean:
	rm -f *.o weather
