#variables
CXX	:= g++
CXXFLAGS := -I "../SFML/include"
LDFLAGS := -L "../SFML/lib" -lsfml-graphics -lsfml-window -lsfml-system

#src files collection
SRCS := main.cpp $(wildcard CppFiles/*.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))


#target
.PHONY: all run clean
all: main

#how every .o from .cpp compiles (pattern rule)
%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

#link to obtain the .exe
main: $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

#target that runs the exe
run: main
	.\main.exe

clean:
	rm -f $(OBJS) main
