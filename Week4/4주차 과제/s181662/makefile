OBJECTS = main.o print.o count.o
SRC = main.c print.c count.c

CC = g++

TARGET = Starwars
CPPFLAGS = -g -c

$(TARGET): $(OBJECTS) header.h
	$(CC) -o $(TARGET) $(OBJECTS)

clean:
	rm $(OBJECTS) $(TARGET)
