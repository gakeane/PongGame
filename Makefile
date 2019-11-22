
CC = g++
FLAGS = -Wall
INCLUDE = -I ./Include
LINK_FILES = -l freeglut -l glu32 -l opengl32 -l glew32
OBJECTS = main.o math_3d.o gl_utils.o model.o

main : main.o math_3d.o gl_utils.o model.o
	$(CC) $(INCLUDE) $(FLAGS) -o main main.o math_3d.o gl_utils.o model.o $(LINK_FILES)

main.o : main.cpp
	$(CC) $(INCLUDE) $(FLAGS) -c main.cpp

math_3d.o : Common/math_3d.cpp Include/math_3d.h
	$(CC) $(INCLUDE) $(FLAGS) -c Common/math_3d.cpp

gl_utils.o : Common/gl_utils.cpp Include/gl_utils.h
	$(CC) $(INCLUDE) $(FLAGS) -c Common/gl_utils.cpp

model.o : Common/model.cpp Include/model.h
	$(CC) $(INCLUDE) $(FLAGS) -c Common/model.cpp



clean:
	rm -rf $(OBJECTS)
