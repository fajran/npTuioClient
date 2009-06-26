// 
//   Copyright (C) 2005, 2006, 2007, 2008, 2009 Free Software Foundation, Inc.
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA


#ifndef PLUGIN_H
#define PLUGIN_H

#include "pluginbase.h"
#include "client.h"

#include <string>
#include <map>

extern NPBool      plugInitialized;

class nsPluginInstance : public nsPluginInstanceBase
{
public:
    nsPluginInstance(nsPluginCreateData* );
    virtual ~nsPluginInstance();

    // We are required to implement these three methods.
    NPBool init(NPWindow *aWindow);
    NPBool isInitialized() { return plugInitialized; }
    void shut();

    NPError GetValue(NPPVariable variable, void *value);
    NPError SetWindow(NPWindow *aWindow);

    NPError NewStream(NPMIMEType type, NPStream *stream, NPBool seekable,
                      uint16_t *stype);
    NPError DestroyStream(NPStream * stream, NPError reason);

    int32_t WriteReady(NPStream *stream);
    int32_t Write(NPStream *stream, int32_t offset, int32_t len, void *buffer);

    NPError WriteStatus(const char *msg) const;

	void event(TuioEventData);


private:
    NPP         _instance;

	int         _port;
	std::string _callback;
};

// end of __PLUGIN_H__
#endif

// Local Variables:
// mode: C++
// End:
