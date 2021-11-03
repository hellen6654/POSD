.PHONY: dirs clean

all: dirs obj/shape.o ut_main

SRC: src/shape.cpp src/rectangle.h src/triangle.h src/ellipse.h src/shape.h \
	src/two_dimensional_coordinate.h src/sort.h src/terminal.h src/compound_shape.h \
	src/shape.cpp src/iterator.h src/null_iterator.h src/scanner.h src/shape_builder.h src/shape_parse.h

TEST: test/ut_rectangle.h test/ut_triangle.h test/ut_ellipse.h test/ut_sort.h test/ut_terminal.h \
	test/ut_compound_shape.h test/ut_iterator.h test/ut_utility.h test/ut_scanner.h test/ut_shape_builder.h test/ut_shape_parse.h

OBJ: obj/shape.o

obj/shape.o: src/shape.cpp src/shape.h
	g++ -std=c++11 -c src/shape.cpp -o obj/shape.o

ut_main: test/ut_main.cpp $(TEST) $(SRC) $(OBJ)
	g++ -std=c++11 test/ut_main.cpp obj/shape.o -o bin/ut_main -lgtest -lpthread

#geo: src/main.cpp $(SRC)
#	g++ -std=c++11  src/main.cpp -o bin/geo

dirs:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -f bin/*
	rm -f obj/*