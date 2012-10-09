CC=g++
CFLAGS=-Wall -DXP_UNIX=1 -fPIC -g

all : npTuioClient.so

npTuioClient.so : plugin.o
	$(CC) $(CFLAGS) -shared $< -o $@

.cc.o :
	$(CC) $(CFLAGS) $< -c -o $@

# vim: set noexpandtab

