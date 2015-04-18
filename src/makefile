SOURCE_FILES	:= $(wildcard *.cpp)
OBJECT_FILES	:= $(patsubst %.cpp,%.o,$(SOURCE_FILES))

CFLAGS			:= -c -g -std=c++0x -Wunused-variable
C_INCLUDE_PATH	:= -Iinclude

MAIN			:= main.exe

.PHONY: all
all: ${MAIN}
	${MAIN}

${MAIN}: ${OBJECT_FILES}
	g++ -o $@ $^ -lsqlite3 -L.

%.o: %.cpp
	gcc -g ${CFLAGS} ${CPPFLAGS} ${C_INCLUDE_PATH} $< -o $@ -lsqlite3 -L.

.PHONY: clean
clean:
	rm -rf *.o ${MAIN}
