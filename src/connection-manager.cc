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

#include "connection-manager.h"

#include <map>

#include "client.h"

class ConnectionManagerData {
 public:
  std::map<int, Client*> clients;
  std::map<Adapter*, Client*> adapter_clients;
};

ConnectionManager::ConnectionManager() {
  data_ = new ConnectionManagerData();
}

ConnectionManager::~ConnectionManager() {
  delete data_;
  data_ = 0; //NULL;
}


void ConnectionManager::Register(Adapter* adapter, const int port) {
  std::map<int, Client*>::iterator it = data_->clients.find(port);

  Client* client;
  if (it == data_->clients.end()) {
    client = new Client(port);
    data_->clients[port] = client;
  }
  else {
    client = it->second;
  }

  if (!client->is_started()) {
    client->Start();
  }

  client->AddAdapter(adapter);
  data_->adapter_clients[adapter] = client;
}

void ConnectionManager::Unregister(Adapter* adapter) {
  Client* client = data_->adapter_clients[adapter];
  client->RemoveAdapter(adapter);

  if (client->get_total_adapters() == 0) {
    client->Stop();
  }

  data_->adapter_clients.erase(adapter);
}

