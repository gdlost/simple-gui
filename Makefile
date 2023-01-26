SRC=Helpers.cc Window.cc Widget.cc Button.cc Checkbox.cc main.cc
OBJ=$(patsubst %.cc,%.o,$(SRC))
CPPFLAGS=$(shell sdl2-config --cflags)

test: $(OBJ)
	g++ $(OBJ) $(shell sdl2-config --libs)

.PHONY: clean
clean:
	rm *.o 
