CC=g++
CFLAGS=-Wall -DXP_UNIX=1 -fPIC -g -I../TuioClient -I../TuioClient/oscpack -DOSC_HOST_LITTLE_ENDIAN

all : npTuioClient.so

npTuioClient.so : plugin.o client.o connection-manager.o adapter.o ../TuioClient/TuioClient.o ../TuioClient/oscpack/osc/OscReceivedElements.o ../TuioClient/oscpack/osc/OscOutboundPacketStream.o ../TuioClient/oscpack/osc/OscTypes.o ../TuioClient/oscpack/osc/OscPrintReceivedElements.o ../TuioClient/oscpack/ip/posix/NetworkingUtils.o ../TuioClient/oscpack/ip/posix/UdpSocket.o ../TuioClient/oscpack/ip/IpEndpointName.o
	$(CC) $(CFLAGS) -shared $+ -o $@

.cc.o :
	$(CC) $(CFLAGS) $< -c -o $@

.cpp.o :
	$(CC) $(CFLAGS) $< -c -o $@

clean :
	rm npTuioClient.so
	rm plugin.o client.o

# vim: set noexpandtab

