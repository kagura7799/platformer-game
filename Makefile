TARGET = platformer-game

SRC_DIR = src
LIB_DIR = /usr/lib

CXX = g++
CXXFLAGS = -std=c++17
LDFLAGS = -L$(LIB_DIR) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRCS = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*/*.cpp $(SRC_DIR)/*/*/*.cpp)
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS) && ./$(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
