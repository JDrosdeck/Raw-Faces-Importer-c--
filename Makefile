CC = g++
CFLAGS = -Wall 
PROG = viewer

SRCS = main.cpp rawImporter.cpp

ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT -pthread
else
	LIBS = -lglut
endif

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
