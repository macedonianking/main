SOURCE_FILES	:= $(wildcard src/*.cpp)
OBJECT_FILES	:= $(patsubst src/%.cpp,bin/%.o,${SOURCE_FILES})

MAIN			:= main.exe

.PHONY: all
all: make_bin_dir ${MAIN}
	${MAIN}

${MAIN} : ${OBJECT_FILES}
	@echo ${OBJECT_FILES}
	g++ -o $@ ${OBJECT_FILES} -lsqlite3 -L.

bin/%.o:src/%.cpp
	g++ -c -Wall -g -Isrc/include -o $@ $<

.PHONY: make_bin_dir
	-mkdir bin

.PHONY: clean
clean:
	rm -rf bin/*.o ${MAIN}