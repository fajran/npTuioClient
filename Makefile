
SRC= \
	./TuioClient/oscpack/ip/IpEndpointName.cpp \
	./TuioClient/oscpack/ip/posix/UdpSocket.cpp \
	./TuioClient/oscpack/ip/posix/NetworkingUtils.cpp \
	./TuioClient/oscpack/osc/OscPrintReceivedElements.cpp \
	./TuioClient/oscpack/osc/OscReceivedElements.cpp \
	./TuioClient/oscpack/osc/OscTypes.cpp \
	./TuioClient/oscpack/osc/OscOutboundPacketStream.cpp \
	./TuioClient/TuioClient.cpp \
	./src/npn_gate.cpp \
	./src/npp_gate.cpp \
	./src/client.cpp \
	./src/np_entry.cpp \
	./src/plugin.cpp

CC=g++
BIN=npTuioClient.so

CFLAGS=-Os -I TuioClient/ -I TuioClient/oscpack/ -I npapi/ -I src/ -DOSC_HOST_LITTLE_ENDIAN
LDFLAGS=-lpthread

all : ${BIN}

clean :
	rm ${BIN}

${BIN} : ${SRC}
	${CC} -o $@ -shared ${CFLAGS} ${LDFLAGS} $+ 

