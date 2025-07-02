CXX = g++
CXXFLAGS = -Wall -std=c++17
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)