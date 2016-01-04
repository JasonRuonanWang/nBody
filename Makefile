CCFLAGS_MAC = -std=c99 -framework GLUT -framework OpenGL -framework Cocoa -I/usr/X11/include
LDFLAGS_MAC = -lglut -lgl -lglu -lX11 -L/usr/X11/lib

CCFLAGS_LIN =
LDFLAGS_LIN = -lglut -lGL -lGLU -lX11 -lm

CC = clang

APP = 3body 

all: $(APP)
	@echo Make done

#%: %.c
#	gcc $^ -o $@ $(INCLUDE_PATH) $(CCFLAGS) $(LIBRARY_PATH) $(LDFLAGS)

clean:
	@rm -f *.o $(APP)


3body: nbody.c 3body.c
	$(CC) nbody.c 3body.c $(LDFLAGS_LIN) $(CCFLAGS_LIN) -o $(APP)
