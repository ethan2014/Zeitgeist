CC	= g++
CFLAGS	= -std=c++14 -Wall -Werror
SOURCES	= src/*.cpp
TARGET	= main
DEBUG	= debug
RELEASE = release

all: $(TARGET)

debug: $(DEBUG)

release: $(RELEASE)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -O0 -o $(TARGET) $(SOURCES)

$(DEBUG): $(SOURCES)
	$(CC) $(CFLAGS) -O0 -g -o $(DEBUG) $(SOURCES)

$(RELEASE): $(SOURCES)
	$(CC) $(CFLAGS) -Ofast -o $(RELEASE) $(SOURCES)

clean:
	rm main
