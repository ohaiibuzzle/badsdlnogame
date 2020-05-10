CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

CC_SDL := $(shell pkg-config --cflags --libs freetype2 sdl2 SDL2_image SDL2_mixer SDL2_ttf) -lb64

LIBRARIES	:=
EXECUTABLE	:= main


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $(CC_SDL) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*