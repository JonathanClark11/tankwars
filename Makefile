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
OBJ=main.o tank.o objreader.o heightfield.o skybox.o texloader.o boundingbox.o projectile.o scenemanager.o


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
