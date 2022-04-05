CCFLAGS_MAC = -framework GLUT -framework OpenGL -framework Cocoa -I/usr/X11/include -Wno-deprecated
LDFLAGS_MAC =-framework OpenGL -framework GLUT -framework Cocoa

CCFLAGS_LIN =
LDFLAGS_LIN =-lglut -lGL -lGLU -lX11 -lm
CC = clang

APP = 3body

all: $(APP)
	@echo Make done

#%: %.c
#	gcc $^ -o $@ $(INCLUDE_PATH) $(CCFLAGS) $(LIBRARY_PATH) $(LDFLAGS)

clean:
	@rm -rf *.o $(APP) *.dSYM


3body: nbody.c 3body.c
	$(CC) nbody.c 3body.c $(LDFLAGS_MAC) $(CCFLAGS_MAC) -o $(APP)

re: clean all
