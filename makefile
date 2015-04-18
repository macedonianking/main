SOURCE_FILES	:= $(wildcard *.cpp)
OBJECT_FILES	:= $(patsubst %.cpp,%.o,$(SOURCE_FILES))

CFLAGS			:= -O0 -g3 -Wall -c -fmessage-length=0
C_INCLUDE_PATH	:= -Iinclude

MAIN			:= main.exe

.PHONY: all
all: ${MAIN}
	${MAIN}

${MAIN}: ${OBJECT_FILES}
	g++ -o $@ $^ -lsqlite3 -L.

%.o: %.cpp
	g++ ${CFLAGS} ${CPPFLAGS} ${C_INCLUDE_PATH} $< -o $@ -lsqlite3 -L.

.PHONY: clean
clean:
	rm -rf *.o ${MAIN}
