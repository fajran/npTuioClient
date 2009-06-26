
SRC=np_entry.cpp npn_gate.cpp npp_gate.cpp plugin.cpp
OBJ=${SRC:.cpp=.o}
BIN=nptuio.so

CC=g++

CFLAGS=`pkg-config --cflags xulrunner-plugin`
LDFLAGS=`pkg-config --libs xulrunner-plugin`

all : ${BIN}

${BIN} : ${OBJ}
	${CC} -v -O3 -shared -o $@ ${LDFLAGS} $+

.cpp.o :
	${CC} -c ${CFLAGS} $<


