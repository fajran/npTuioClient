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

#ifndef CONNECTION_MANAGER_
#define CONNECTION_MANAGER_

class Adapter;
class ConnectionManagerData;

class ConnectionManager {
 public:
  ConnectionManager();
  ~ConnectionManager();

  void Register(Adapter* adapter, const int port);
  void Unregister(Adapter* adapter);

 private:
  ConnectionManagerData* data_;
};

#endif

