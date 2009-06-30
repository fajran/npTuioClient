//   
// Copyright (C) 2009  Fajran Iman Rusadi
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include "client.h"

#include <TuioClient.h>
#include <TuioListener.h>
#include <TuioObject.h>
#include <TuioCursor.h>

static inline void call(TuioEvent type, long sid, int fid, float x, float y, float a)
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

