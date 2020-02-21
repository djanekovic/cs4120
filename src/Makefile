OBJ = main.o lex.yy.o xi_driver.o
INCLUDE = -I../include
CXXFLAGS = -g -Wall -Wextra -MMD $(INCLUDE)
DEPENDS = ${OBJ:.o=.d}
CXX = clang++

all: xic

xic: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(LDFLAGS)

.PHONY: ley.yy.cc

lex.yy.cc: xi++-scanner.ll
	flex -c++ -d $^

clean:
	rm -f $(OBJ)

-include ${DEPENDS}
