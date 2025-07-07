# Build automation: sends the .exe (the binary-compiled C code) to the
# bin folder (instead of right next to source file) for better organization,
# which will be ignored by git (gitignore)
#
# To compile the program:
# make
# 
# To compile and run:
# make run
# 
# To clean up .exe files:
# make clean

BIN_DIR = bin
SRC_DIR = src
TARGET = $(BIN_DIR)/todolist.exe
SRC = $(SRC_DIR)/todolist.c

all: $(TARGET)

$(TARGET): $(SRC)
	gcc $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	del $(BIN_DIR)\*.exe