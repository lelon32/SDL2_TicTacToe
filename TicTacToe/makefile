###
### Program Name: TicTacToe
### Author: Long Le
### Description: Basic makefile 
###

# Compiler
CXX = i686-w64-mingw32-c++

# Compiler flags
CXXFLAGS  = -std=c++11
CXXFLAGS += -g
CXXFLAGS += -Wall
CXXFLAGS += -Wextra
CXXFLAGS += -pedantic-errors

INCLUDE_PATHS  = -IC:\cygwin64\usr\i686-w64-mingw32\sys-root\mingw\include\SDL2
INCLUDE_PATHS += -IC:\GLlib\include\GL
	
LIBRARY_PATHS  = -LC:\cygwin64\usr\i686-w64-mingw32\sys-root\mingw\lib
LIBRARY_PATHS += -LC:\GLlib\lib

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS  = -lmingw32
LINKER_FLAGS += -lSDL2main
LINKER_FLAGS += -lSDL2
LINKER_FLAGS += -lSDL2_image
LINKER_FLAGS += -lSDL2_ttf
LINKER_FLAGS += -lopengl32 
LINKER_FLAGS += -lglew32

# Source files
SRCS = $(wildcard *.cpp) 

# Create an object for each source file
OBJS = $(SRCS:.cpp=.o)

# Header files
HEADERS = $(wildcard *.hpp) 

EXECUTABLE = TicTacToe 

# target: dependencies
# rules to build
${EXECUTABLE} : ${OBJS} ${HEADERS}
	${CXX} ${OBJS} ${LIBRARY_PATHS} ${LINKER_FLAGS} -o ${EXECUTABLE} 

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} ${INCLUDE_PATHS} -c $(@:.o=.cpp)'sdl2-config --cflags --libs' 

# target: clean
clean: $(CLEAN)
	@echo "Removed object files"
	@echo "Removed" ${EXECUTABLE}
	@rm *.exe ${OBJS} ${EXECUTABLE} 
