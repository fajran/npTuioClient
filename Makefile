
SRC=np_entry.cpp npn_gate.cpp npp_gate.cpp plugin.cpp client.cpp
OBJ=${SRC:.cpp=.o}
BIN=nptuio.so

CC=g++

CFLAGS=-Inpapi `pkg-config --cflags xulrunner-plugin` -Ituio -Ituio/oscpack
LDFLAGS=`pkg-config --libs xulrunner-plugin`

all : ${BIN}

${BIN} : ${OBJ}
	${CC} -v -O3 -shared -o $@ ${LDFLAGS} *.o

.cpp.o :
	${CC} -c ${CFLAGS} $<

clean :
	rm ${OBJ}

