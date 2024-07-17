CXX		=	g++
CXXFLAGS=	-Wall -g


LIBS	= 	yaml-cpp

ARG_LIBS=	pkgconf --cflags --libs $(LIBS)

D_SRC	=	src
D_IMPL	=	$(D_SRC)/impl
D_HEAD	=	$(D_SRC)/headers

MAINFILE=	$(D_SRC)/main

VERSION	=	v0.1

D_BIN	=	build/$(VERSION)/bin
D_OBJ	=	build/$(VERSION)/obj

BINARY	=	.note

SOURCES	= 	$(wildcard $(D_IMPL)/*.cpp $(MAINFILE).cpp)
OBJECTS	=	$(patsubst $(D_SRC)/%.cpp, $(D_OBJ)/%.o, $(SOURCES))

all: $(D_BIN)/$(BINARY)

$(D_BIN)/$(BINARY): $(OBJECTS)
	@mkdir -p $(D_BIN)
	$(CXX) $(CXXFLAGS) `$(ARG_LIBS)` -o $@ $^

$(D_OBJ)/%.o: $(D_SRC)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean:
	rm -rf $(D_OBJ) $(D_BIN)

.PHONY: all clean
