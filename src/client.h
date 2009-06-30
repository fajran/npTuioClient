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

