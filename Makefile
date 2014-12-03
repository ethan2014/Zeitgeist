CC	= g++
CFLAGS	= -std=c++14 -Wall -Werror
SOURCES	= src/*.cpp src/mongoose/*.cpp
TARGET	= main
DEBUG	= debug.out
RELEASE = release.out

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
