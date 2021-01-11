SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst %.cpp, %.o, ${SRCS})
BIN = ImageSheeter.out
TESTS = $(patsubst %.cpp, %.out, $(wildcard tests/*.cpp))
SDL_INCLUDES = `sdl2-config --cflags` `pkg-config --cflags SDL2_image SDL2_ttf`
SDL_LIBS = `sdl2-config --libs` `pkg-config --libs SDL2_image SDL2_ttf`
DEBUG =

${BIN}:

${TESTS}:%.out:%.cpp
	$(CXX) $^ -o $@ ${OBJS} ${SDL_INCLUDES} ${DEBUG} ${SDL_LIBS} -Iinclude -std=c++17

%.o:%.cpp
	$(CXX) $^ -c -o $@ ${SDL_INCLUDES} ${DEBUG} -Iinclude -std=c++17

test:${TESTS}

ImageSheeter.out:main.cpp ${OBJS}
	$(CXX) $^ -o $@ ${SDL_INCLUDES} ${SDL_LIBS} ${DEBUG} -Iinclude -std=c++17

.PHONY:clean test
clean:
	-rm *.out
	-rm ${OBJS}
	-rm tests/*.o
	-rm ${TESTS}
	-rm *.o

