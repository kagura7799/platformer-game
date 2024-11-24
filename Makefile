TARGET = survive-from-zombie-game

SRC_DIR = src
BUILD_DIR = build
LIB_DIR = /usr/lib

CXX = g++
CXXFLAGS = -std=c++17
LDFLAGS = -L$(LIB_DIR) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRCS = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*/*.cpp $(SRC_DIR)/*/*/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

define MKDIRS
    @mkdir -p $(dir $@)
endef

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS) && ./$(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(MKDIRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
