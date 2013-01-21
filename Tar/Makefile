#create exe file
TARGET_NAME = main
SRC = $(shell ls *.cpp)
OBJ0 = $(SRC:.c=.o)
OBJ = $(OBJ0:.cpp=.o)

CC = g++

CFLAGS = -Wall -Wextra -O3
LDLIBS = -ltar
TARGET = $(TARGET_NAME)

.SUFFIXES: .c .cpp .o
.PHONY: clean all run depend remake

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDLIBS)
.cpp.o:
	$(CC) -c $< -o $@ $(CFLAGS)
.c.o:
	$(CC) -c $< -o $@ $(CFLAGS)


run: all
	@./$(TARGET) test.xml

clean:
	@rm -f $(OBJ) $(TARGET)

remake: clean all

depend:
	$(CC) -MM $(SRC) > depend.inc
-include depend.inc

