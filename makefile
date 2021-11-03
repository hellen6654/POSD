.PHONY: dirs clean

all: dirs ut_main

SRC: src/shape.cpp src/rectangle.h src/triangle.h src/ellipse.h src/shape.h src/two_dimensional_coordinate.h src/sort.h src/terminal.h src/compound_shape.h src/shape.cpp
TEST: test/ut_rectangle.h test/ut_triangle.h test/ut_ellipse.h test/ut_sort.h test/ut_terminal.h test/ut_compound_shape.h

ut_main: test/ut_main.cpp $(TEST) $(SRC)
	g++ -std=c++11 test/ut_main.cpp -o bin/ut_main -lgtest -lpthread

#geo: src/main.cpp $(SRC)
#	g++ -std=c++11  src/main.cpp -o bin/geo

dirs:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -f bin/*
