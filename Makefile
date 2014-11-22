CC	= g++
CFLAGS	= -std=c++11
SOURCES	= *.cpp
TARGET	= main

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm main
