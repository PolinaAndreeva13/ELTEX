TARGET = tcp_server

SOURCES = tcp_server.c

CC = gcc

CFLAGS = -Wall -Wextra

LDFLAGS =

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)
