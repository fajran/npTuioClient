
#include "client.h"

#include <TuioClient.h>
#include <TuioListener.h>
#include <TuioObject.h>
#include <TuioCursor.h>

inline void call(TuioEvent type, long sid, int fid, float x, float y, float a)
{
	TuioEventData data;
	data.type = type;
	data.sid = sid;
	data.fid = fid;
	data.x = x;
	data.y = y;
	data.a = a;
	tuio_callback(data);
}

class Listener : public TuioListener
{
public:
	Listener() { };
	~Listener() { };

	void addTuioObject(TuioObject *object)
	{
		call(TE_OBJECT_ADD,
			object->getSessionID(), object->getFiducialID(),
			object->getX(), object->getY(), object->getAngle());
	}

	void updateTuioObject(TuioObject *object)
	{
		call(TE_OBJECT_UPDATE,
			object->getSessionID(), object->getFiducialID(),
			object->getX(), object->getY(), object->getAngle());
	}

	void removeTuioObject(TuioObject *object)
	{
		call(TE_OBJECT_REMOVE,
			object->getSessionID(), object->getFiducialID(),
			object->getX(), object->getY(), object->getAngle());
	}
	
	void addTuioCursor(TuioCursor *cursor)
	{
		call(TE_CURSOR_ADD,
			cursor->getSessionID(), cursor->getFingerID(),
			cursor->getX(), cursor->getY(), 0);
	}

	void updateTuioCursor(TuioCursor *cursor)
	{
		call(TE_CURSOR_UPDATE,
			cursor->getSessionID(), cursor->getFingerID(),
			cursor->getX(), cursor->getY(), 0);
	}

	void removeTuioCursor(TuioCursor *cursor)
	{
		call(TE_CURSOR_REMOVE,
			cursor->getSessionID(), cursor->getFingerID(),
			cursor->getX(), cursor->getY(), 0);
	}
	
	void refresh(long timestamp) 
	{
	}
};

static TuioClient* client = 0;
static Listener* listener = 0;

void tuio_start(int port)
{
	if (!client) {
		listener = new Listener();

		client = new TuioClient(port);
		client->addTuioListener(listener);
		client->start();
	}
}

void tuio_stop()
{
	client->stop();
	delete listener;
	delete client;

	client = 0;
	listener = 0;
}

