SFML_PATH = /usr/local/Cellar/sfml/2.6.2

CXX = g++
CXXFLAGS = -std=c++17 -I$(SFML_PATH)/include
LDFLAGS = -L$(SFML_PATH)/lib -lsfml-graphics -lsfml-window -lsfml-system

SRC = practice.cpp
TARGET = sfml_app

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
