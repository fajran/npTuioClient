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

#ifndef EVENT_H_
#define EVENT_H_

typedef enum {
  EVENT_OBJECT_ADD    = 0,
  EVENT_OBJECT_UPDATE = 1,
  EVENT_OBJECT_REMOVE = 2,
  EVENT_CURSOR_ADD    = 3,
  EVENT_CURSOR_UPDATE = 4,
  EVENT_CURSOR_REMOVE = 5
} TuioEventType;

typedef struct {
  TuioEventType type;
  long fid;
  int sid;
  float x;
  float y;
  float a;
} TuioEvent;

#endif

