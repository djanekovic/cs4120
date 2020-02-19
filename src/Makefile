OBJ = main.o lex.yy.o xi_driver.o
INCLUDE = -I../include
CXXFLAGS = -g -Wall -Wextra -MMD $(INCLUDE)
DEPENDS = ${OBJ:.o=.d}
CXX = clang++

all: xic

xic: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(LDFLAGS)

.PHONY: xi++

clean:
	rm -f $(OBJ)

-include ${DEPENDS}
