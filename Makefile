# OS X
ifeq ("$(shell uname)", "Darwin")
  CXXFLAGS = -I/usr/include
  LIB = -framework OpenGL -framework GLUT
#endif

# Linux 
#ifeq ("$(shell uname)", "linux")
else
  CXXFLAGS = -I/usr/include 
  LIB = -lGL -lGLU -lglut
endif


BIN=tankwars
OBJ=camera.o main.o tank.o objreader.o heightfield.o


default: build

build: $(BIN)

test: build
	./$(BIN)

%.o: %.cpp
	g++ -c -g $(CXXFLAGS) -o $@ $<

$(BIN): $(OBJ)
	g++ -g -o $@ $(OBJ) $(LIB)

clean:
	- rm -f $(BIN) $(OBJ)