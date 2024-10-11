TARGET = platformer-game

SRC_DIR = src
INC_DIR = include
LIB_DIR = /usr/lib

CXX = g++
CXXFLAGS = -I$(INC_DIR) -std=c++17
LDFLAGS = -L$(LIB_DIR) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/Game.cpp $(SRC_DIR)/Sounds.cpp

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS) && ./platformer-game

clean:
	rm -f $(TARGET)
