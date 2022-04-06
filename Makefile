CCFLAGS_MAC = -framework GLUT -framework OpenGL -framework Cocoa -I/usr/X11/include -Wno-deprecated
LDFLAGS_MAC =-framework OpenGL -framework GLUT -framework Cocoa

CCFLAGS_LIN =
LDFLAGS_LIN =-lglut -lGL -lGLU -lX11 -lm

CC1=clang
CC2=gcc-6

all: 3body nbody
	@echo Make done

clean:
	@rm -rf *.o 3body nbody *.dSYM


3body: nbody.c 3body.c
	$(CC1) nbody.c 3body.c $(LDFLAGS_MAC) $(CCFLAGS_MAC) -o 3body_$(CC1)
	$(CC2) nbody.c 3body.c $(LDFLAGS_MAC) $(CCFLAGS_MAC) -o 3body_$(CC2)

nbody: nbody.c fileloader.c
	$(CC1) nbody.c fileloader.c $(LDFLAGS_MAC) $(CCFLAGS_MAC) -o nbody_$(CC1)
	$(CC2) nbody.c fileloader.c $(LDFLAGS_MAC) $(CCFLAGS_MAC) -o nbody_$(CC2)

re: clean
	make -j all
