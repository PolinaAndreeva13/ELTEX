# Название цели сборки (исполняемого файла)
TARGET = tcp_server

# Список исходных файлов
SOURCES = tcp_server.c

# Команда компиляции
CC = gcc

# Флаги компиляции
CFLAGS = -Wall -Wextra

# Флаги линковки
LDFLAGS =

# Цель по умолчанию (выполняется при вызове make без аргументов)
all: $(TARGET)

# Правило сборки исполняемого файла из исходных файлов
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

# Цель "clean" для удаления собранных файлов
clean:
	rm -f $(TARGET)
