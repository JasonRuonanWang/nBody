INCLUDE_PATH = -I/usr/X11/include 
LIBRARY_PATH = -L/usr/X11/lib 
CCFLAGS = -std=c99 -framework GLUT -framework OpenGL -framework Cocoa
LDFLAGS = -lglut -lgl -lglu -lX11 -lpthread 

# the directories containing the OpenGL libraries, f90gl libraries, GLUT
# libraries, and f90gl GLUT libraries
OGLLIBDIR = -L/usr/X11/lib

# the X11 libraries
X11LIB = -framework GLUT -framework OpenGL -framework Cocoa

# the f90 compiler flag for specifying the location of MOD files
MODS = -I/usr/X11/include/GL

# the directory containing the X11 libraries
X11LIBDIR =

GCC = gcc

APP = nbody 

all: $(APP)
	@echo Make done

#%: %.c
#	gcc $^ -o $@ $(INCLUDE_PATH) $(CCFLAGS) $(LIBRARY_PATH) $(LDFLAGS)

clean:
	@rm -f *.o $(APP)


nbody: nbody.c
	$(GCC) nbody.c $(INCLUDE_PATH) $(LIBRARY_PATH) $(LDFLAGS) $(CCFLAGS) -o nbody
