CFLAGS := -g
INCLUDE := -I ~/include
LDFLAGS := -L ~/lib -lsense
%.o: %.c
	cc -c $(CFLAGS) $< $(INCLUDE)

joystick: joystick.o
	cc -o joystick $(INCLUDE) joystick.o $(LDFLAGS)

clean:
	rm -f *.o joystick
