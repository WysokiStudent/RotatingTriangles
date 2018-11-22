CXX=clang++
CXXFLAGS=-Weverything -Wno-c++98-compat -std=c++17 -O3
LDFLAGS=-lGL -lGLU -lglut
OUT=application

$(OUT):main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.Phony:
clean:
	rm -f $(OUT)

