MAIN	:= main.exe
SOURCE_FILES	:= main.cpp
OBJECT_FILES	:= $(patsubst %.cpp,%.o,$(SOURCE_FILES))

LINK_LIBRARIES	:= 

.PHONY: ALL
ALL: ${MAIN}
	${MAIN}

${MAIN}: ${OBJECT_FILES}
	gcc -o $@ $^ ${LINK_LIBRARIES}

%.o: %.cpp
	gcc -c -std=c++0x $< -o $@ ${LINK_LIBRARIES}

.PHONY: clean
clean:
	rm -rf *.o ${MAIN}