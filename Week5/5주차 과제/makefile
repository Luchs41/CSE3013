OBJECTS = main.o Str.o
SRC = main.cpp Str.cpp

CC = g++

TARGET = main
CPPFLAGS = -g -c

$(TARGET): $(OBJECTS) Str.h
	$(CC) -o $(TARGET) $(OBJECTS)

clean:
	rm $(OBJECTS) $(TARGET)
