.PHONY: clean

CXX = g++
CXXFLAGS = -I include -g
CFILES = $(shell find src -name "*.cpp")

OBJS = $(CFILES:.cpp=.o)
TARGET = main

RM = -rm -rf

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

%.o : %(.cpp)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(TARGET) $(OBJS)