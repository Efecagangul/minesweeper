CXX = g++
CXXFLAGS = -std=c++17 -I.

# Use pkg-config to get correct SFML flags on Linux
PKG_CFLAGS  := $(shell pkg-config --cflags sfml-graphics sfml-window sfml-system 2>/dev/null)
PKG_LIBS    := $(shell pkg-config --libs   sfml-graphics sfml-window sfml-system 2>/dev/null)

ifneq ($(PKG_CFLAGS),)
    CXXFLAGS += $(PKG_CFLAGS)
endif

ifeq ($(strip $(PKG_LIBS)),)
	# Fallback if pkg-config didn't find SFML (adjust paths/libs as needed)
	LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
else
	LDFLAGS = $(PKG_LIBS)
endif

SOURCES = main.cpp MinesweeperBoard.cpp MSBoardTextView.cpp MSTextController.cpp MSSFMLView.cpp MSSFMLController.cpp
HEADERS = Field.h GameMode.h MinesweeperBoard.h MSBoardTextView.h MSTextController.h MSSFMLView.h MSSFMLController.h
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
.PHONY: all clean
