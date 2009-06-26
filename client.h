#ifndef CLIENT_H_
#define CLIENT_H_

enum TuioEvent {
	TE_OBJECT_ADD    = 0,
	TE_OBJECT_UPDATE = 1,
	TE_OBJECT_REMOVE = 2,
	TE_CURSOR_ADD    = 3,
	TE_CURSOR_UPDATE = 4,
	TE_CURSOR_REMOVE = 5,
};

typedef struct {
	TuioEvent type;
	long      fid;
	int       sid;
	float     x;
	float     y;
	float     a;
} TuioEventData;

void tuio_start(int);
void tuio_stop();

extern void tuio_callback(TuioEventData);

#endif

