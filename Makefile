CFLAGS = -g -std=c++11 `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`

SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

%.o : %.cpp 
	g++ -c $(CFLAGS) $<

image: $(OBJECTS)
	g++ $(CFLAGS) -o $@ $(OBJECTS) $(LIBS)

clean:
	rm *.o image 
