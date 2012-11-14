CC=g++
CFLAGS=-Wall -DXP_UNIX=1 -fPIC -g -ITuioClient -ITuioClient/oscpack -DOSC_HOST_LITTLE_ENDIAN
TUIO_CLIENT_SRC=TuioClient/TuioClient.cpp \
	TuioClient/oscpack/osc/OscReceivedElements.cpp \
	TuioClient/oscpack/osc/OscOutboundPacketStream.cpp \
	TuioClient/oscpack/osc/OscTypes.cpp \
	TuioClient/oscpack/osc/OscPrintReceivedElements.cpp \
	TuioClient/oscpack/ip/posix/NetworkingUtils.cpp \
	TuioClient/oscpack/ip/posix/UdpSocket.cpp \
	TuioClient/oscpack/ip/IpEndpointName.cpp
PLUGIN_SRC=src/plugin.cc \
	src/client.cc \
	src/connection-manager.cc \
	src/adapter-npapi.cc

TUIO_CLIENT_OBJ=$(TUIO_CLIENT_SRC:.cpp=.o)
PLUGIN_OBJ=$(PLUGIN_SRC:.cc=.o)

TARGET=npTuioClient.so

all : $(TARGET)

$(TARGET) : $(PLUGIN_OBJ) $(TUIO_CLIENT_OBJ)
	$(CC) $(CFLAGS) -shared $+ -o $@

.cc.o :
	$(CC) $(CFLAGS) $< -c -o $@

.cpp.o :
	$(CC) $(CFLAGS) $< -c -o $@

clean :
	rm $(TARGET)
	rm $(PLUGIN_OBJ)
	rm $(TUIO_CLIENT_OBJ)


