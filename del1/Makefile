CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2
LDFLAGS =

TARGET = biprep
SRCS = main.cpp Biprep.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
test: $(TARGET)
	./biprep --run-tests

.PHONY: all clean test