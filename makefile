ifeq (${OS},Windows_NT)
MAIN	:= main.exe
else
MAIN	:= main
endif

F_USE_CURL 				:= 0
ifeq (${F_USE_CURL},1)
	CURL_HOME			:= /usr/share/curl
	CURL_SOURCE_FILES 	:= curl_main.cpp
	CURL_INCLUDE_PATH	:= -I${CURL_HOME}/include
	CURL_LIB_PATH		:= -L${CURL_HOME}/lib
	CURL_LINK_FLAG		:= -lcurl
	CURL_D_FLAG			:= -DF_USE_CURL
else
	CURL_SOURCE_FILES	:=
	CURL_INCLUDE_PATH	:= 
	CURL_D_FLAG			:=
	CURL_LINK_FLAG		:= 
endif

SOURCE_FILES	:= 	main.cpp \
					local_signal.cpp \
					main_sort.cpp \
					main_print.cpp ${CURL_SOURCE_FILES}

OBJECT_FILES	:= $(patsubst %.cpp,%.o,$(SOURCE_FILES))


CFLAGS			:= -c -g -std=c++0x -Wunused-variable
CPPFLAGS		:= ${CURL_D_FLAG}
C_INCLUDE_PATH	:= ${CURL_INCLUDE_PATH}
LINK_PATH		:= ${CURL_LIB_PATH}
LINK_LIBS		:= ${CURL_LINK_FLAG}

.PHONY: all
all: ${MAIN}

${MAIN}: ${OBJECT_FILES}
	g++ -o $@ $^ ${LINK_PATH} ${LINK_LIBS}

%.o: %.cpp
	gcc -g ${CFLAGS} ${CPPFLAGS} ${C_INCLUDE_PATH} $< -o $@ ${LINK_PATH} ${LINK_LIBS}

.PHONY: clean
clean:
	rm -rf *.o ${MAIN}
