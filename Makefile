CCFLAGS_MAC = -framework GLUT -framework OpenGL -framework Cocoa -I/usr/X11/include -Wno-deprecated
LDFLAGS_MAC =-framework OpenGL -framework GLUT -framework Cocoa

CCFLAGS_LIN =
LDFLAGS_LIN =-lglut -lGL -lGLU -lX11 -lm

CC=clang
CC=gcc-10

all: 3body fileloader
	@echo Make done

clean:
	@rm -rf *.o 3body fileloader *.dSYM


3body: nbody.c 3body.c
	$(CC) nbody.c 3body.c $(LDFLAGS_MAC) $(CCFLAGS_MAC) -o 3body

fileloader: nbody.c fileloader.c
	$(CC) nbody.c fileloader.c $(LDFLAGS_MAC) $(CCFLAGS_MAC) -o fileloader

re: clean
	make -j all
