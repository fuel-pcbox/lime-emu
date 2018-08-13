CXX=g++
CFLAGS=-std=c++14 -g
LIBS=
VPATH=src
OBJ = arm.o \
cp15.o \
main.o

all: $(OBJ)
	$(CXX) $(CFLAGS) $(OBJ) -o lime $(LIBS)

clean:
	rm *.o && rm lime

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<