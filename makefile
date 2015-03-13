MAIN	:= main
SOURCE_FILES	:= 	main.cpp \
					local_signal.cpp \
					main_sort.cpp \
					curl_main.cpp

OBJECT_FILES	:= $(patsubst %.cpp,%.o,$(SOURCE_FILES))
CURL_HOME		:= /usr/share/curl

C_INCLUDE_PATH	:= -I${CURL_HOME}/include
LINK_PATH	:= -L${CURL_HOME}/lib
LINK_LIBS	:= -lcurl

.PHONY: ALL
ALL: ${MAIN}
	./${MAIN}

${MAIN}: ${OBJECT_FILES}
	gcc -o $@ $^ ${LINK_PATH} ${LINK_LIBS}

%.o: %.cpp
	gcc -c -std=c++0x ${C_INCLUDE_PATH} $< -o $@ ${LINK_PATH} ${LINK_LIBS}

.PHONY: clean
clean:
	rm -rf *.o ${MAIN}