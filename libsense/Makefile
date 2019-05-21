INCLUDES=include
CARGS = 


lib: lib/libsense.a

src/obj/framebuffer.o: src/framebuffer/framebuffer.c include/framebuffer.h
	gcc $(CARGS) -c -o src/obj/framebuffer.o src/framebuffer/framebuffer.c -I $(INCLUDES)

src/obj/i2c.o: src/i2c/i2c.c include/i2c.h
	gcc $(CARGS) -c -o src/obj/i2c.o src/i2c/i2c.c -I $(INCLUDES)

src/obj/humidity_temp.o: src/humidity_temp/humidity_temp.c src/humidity_temp/hw.h include/i2c.h
	gcc $(CARGS) -c -o src/obj/humidity_temp.o src/humidity_temp/humidity_temp.c -I $(INCLUDES)

src/obj/pressure.o: src/pressure/pressure.c include/i2c.h src/pressure/hw.h
	gcc $(CARGS) -c -o src/obj/pressure.o src/pressure/pressure.c -I $(INCLUDES)

src/obj/joystick.o: src/joystick/joystick.c include/joystick.h
	gcc $(CARGS) -c -o src/obj/joystick.o src/joystick/joystick.c -I $(INCLUDES)

src/obj/gyro.o: src/gyro/gyro.c include/coord.h
	gcc $(CARGS) -c -o src/obj/gyro.o src/gyro/gyro.c -I $(INCLUDES)

src/obj/mag.o: src/mag/mag.c include/coord.h
	gcc $(CARGS) -c -o src/obj/mag.o src/mag/mag.c -I $(INCLUDES)
src/obj/font.o: src/font/font.c include/framebuffer.h
	gcc $(CARGS) -c -o src/obj/font.o src/font/font.c -I $(INCLUDES)

lib/libsense.a: src/obj/framebuffer.o src/obj/i2c.o src/obj/humidity_temp.o src/obj/pressure.o src/obj/joystick.o src/obj/gyro.o src/obj/mag.o src/obj/font.o
	ar rcs $@ $^

lib-clean: 
	rm -f lib/libsense.a src/obj/*.o
install: lib/libsense.a ~/lib ~/include/sense
	cp lib/libsense.a ~/lib
	cp include/*.h ~/include
~/include/sense:
	mkdir -p ~/include/sense
~/lib:
	mkdir ~/lib
uninstall:
	rm -rf ~/include/sense
	rm -f ~/lib/libsense.a

all: lib 

clean: lib-clean 
