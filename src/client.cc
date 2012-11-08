//
// Copyright (C) 2009-2012  Fajran Iman Rusadi
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

#include "event.h"
#include "adapter.h"
#include "debug.h"

#include <list>

//
// Tuio Listener
//

class Listener : public TuioListener {
 public:
  Listener(std::list<Adapter*>* adapters) : adapters_(adapters) {
  };

  ~Listener() {
  };

  void addTuioObject(TuioObject *object) {
    TuioEvent event;
    event.type = EVENT_OBJECT_ADD;
    event.fid = object->getFiducialID();
    event.sid = object->getSessionID();
    event.x = object->getX();
    event.y = object->getY();
    event.a = object->getAngle();

    Invoke(event);
  }

  void updateTuioObject(TuioObject *object) {
    TuioEvent event;
    event.type = EVENT_OBJECT_UPDATE;
    event.fid = object->getFiducialID();
    event.sid = object->getSessionID();
    event.x = object->getX();
    event.y = object->getY();
    event.a = object->getAngle();

    Invoke(event);
  }

  void removeTuioObject(TuioObject *object) {
    TuioEvent event;
    event.type = EVENT_OBJECT_REMOVE;
    event.fid = object->getFiducialID();
    event.sid = object->getSessionID();
    event.x = object->getX();
    event.y = object->getY();
    event.a = object->getAngle();

    Invoke(event);
  }

  void addTuioCursor(TuioCursor *cursor) {
    TuioEvent event;
    event.type = EVENT_CURSOR_ADD;
    event.fid = cursor->getFingerID();
    event.sid = cursor->getSessionID();
    event.x = cursor->getX();
    event.y = cursor->getY();
    event.a = 0;

    Invoke(event);
  }

  void updateTuioCursor(TuioCursor *cursor) {
    TuioEvent event;
    event.type = EVENT_CURSOR_UPDATE;
    event.fid = cursor->getFingerID();
    event.sid = cursor->getSessionID();
    event.x = cursor->getX();
    event.y = cursor->getY();
    event.a = 0;

    Invoke(event);
  }

  void removeTuioCursor(TuioCursor *cursor) {
    TuioEvent event;
    event.type = EVENT_CURSOR_REMOVE;
    event.fid = cursor->getFingerID();
    event.sid = cursor->getSessionID();
    event.x = cursor->getX();
    event.y = cursor->getY();
    event.a = 0;

    Invoke(event);
  }

  void refresh(long timestamp) {
  }

 private:
  void Invoke(TuioEvent event) {
    std::list<Adapter*>::iterator end = adapters_->end();

    std::list<Adapter*>::iterator it;
    for (it=adapters_->begin(); it != end; it++) {
      Adapter* adapter = (Adapter*)*it;
      adapter->Invoke(event);
    }
  }

  std::list<Adapter*>* adapters_;
};

//
// Client Data
//

class ClientData {
 public:
  TuioClient* tuio_client;
  Listener* listener;

  std::list<Adapter*> adapters;
};

//
// Client
//

Client::Client(const int port) : port_(port) {
  data_ = new ClientData();
}

Client::~Client() {
  D("Client::Start()");
  if (is_started()) Stop();

  delete data_;
  data_ = NULL;
}

bool Client::Start() {
  D("Client::Start()");
  if (is_started()) Stop();

  data_->tuio_client = new TuioClient(port_);
  if (!data_->tuio_client->socket) {
    // Unable to bind port
    delete data_->tuio_client;
    data_->tuio_client = NULL;
    D("Client::Start(): FAIL");
    return false;
  }

  data_->listener = new Listener(&data_->adapters);
  data_->tuio_client->addTuioListener(data_->listener);
  data_->tuio_client->start();

  D("Client::Start(): OK");
  return true;
}

void Client::Stop() {
  D("Client::Stop()");
  if (!is_started()) return;

  data_->tuio_client->removeTuioListener(data_->listener);
  data_->tuio_client->stop();

  delete data_->tuio_client;
  data_->tuio_client = NULL;

  delete data_->listener;
  data_->listener = NULL;

  D("Client::Stop(): OK");
}

bool Client::is_started() {
  return data_->tuio_client != NULL;
}

void Client::AddAdapter(Adapter* adapter) {
  data_->adapters.push_back(adapter);
}

void Client::RemoveAdapter(Adapter* adapter) {
  data_->adapters.remove(adapter);
}

int Client::get_total_adapters() {
  return data_->adapters.size();
}

