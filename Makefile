# CC = gcc
# CFLAGS = -I./include -Wall

# SRC = src/main.c src/customer.c
# OBJ = $(SRC:.c=.o)

# TARGET = bank_app

# all: $(TARGET)

# $(TARGET): $(OBJ)
# 	$(CC) -o $(TARGET) $(OBJ)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	rm -f $(OBJ) $(TARGET)

# Compiler and flags
CC = gcc
CFLAGS = -I./include -Wall

# Source files
SRC = src/main.c src/customer.c
OBJ = $(SRC:.c=.o)

# Target executable name
TARGET = bank_app

# Platform detection
ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXE = .exe
else
    RM = rm -f
    EXE =
endif

# Targets
all: $(TARGET)

$(TARGET): $(OBJ)
		$(CC) -o $(TARGET)$(EXE) $(OBJ)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJ) $(TARGET)$(EXE)
