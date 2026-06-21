CC = gcc
CFLAGS = -Wall -Wextra -std=c99
IFLAGS = -Iinclude

# Source and Object files
SOURCES = src/process.c src/scheduler.c src/display.c src/queue.c src/file_handler.c
OBJECTS = $(SOURCES:.c=.o)
MAIN = main.c
MAIN_OBJ = main.o
EXECUTABLE = bin/process_manager

# Build targets
all: clean $(EXECUTABLE)

$(EXECUTABLE): $(MAIN_OBJ) $(OBJECTS)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ $^
	@echo "✓ Build successful! Executable: $(EXECUTABLE)"

%.o: %.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

run: all
	./$(EXECUTABLE)

clean:
	rm -f $(OBJECTS) $(MAIN_OBJ) $(EXECUTABLE)
	@echo "✓ Cleaned up object files and executable"

rebuild: clean all

help:
	@echo "Available targets:"
	@echo "  make all       - Build the project"
	@echo "  make run       - Build and run the project"
	@echo "  make clean     - Remove object files and executable"
	@echo "  make rebuild   - Clean and rebuild"
	@echo "  make help      - Show this help message"

.PHONY: all run clean rebuild help
