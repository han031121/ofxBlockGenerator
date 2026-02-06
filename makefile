CXX = g++
CXXFLAGS = -Wall -O2

SRC_DIR = src
BUILD_DIR = build

SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/generateBlock.cpp \
       $(SRC_DIR)/setWeight.cpp \
       $(SRC_DIR)/utility.cpp \
	   $(SRC_DIR)/setStatus.cpp

OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
TARGET = $(BUILD_DIR)/main.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	$(TARGET)

clean:
	del /Q $(BUILD_DIR)\*.o $(TARGET) 2>nul
