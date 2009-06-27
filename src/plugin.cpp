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

#include "plugin.h"

#include <iostream>
#include <sstream>
#define D(s) /*std::cerr << s << std::endl;*/

#include <set>

#define MIME_TYPES_HANDLED  "application/x-tuio"
// The name must be this value to get flash movies that check the
// plugin version to load.
#define PLUGIN_NAME    "TUIO Client"
#define MIME_TYPES_DESCRIPTION  MIME_TYPES_HANDLED":tuio:"PLUGIN_NAME

#define PLUGIN_DESCRIPTION "TUIO Client plugin"

extern NPNetscapeFuncs NPNFuncs;

NPBool plugInitialized = FALSE;

static std::set<nsPluginInstance*> instances;

void tuio_callback(TuioEventData data)
{
	std::set<nsPluginInstance*>::iterator iter;
	for (iter = instances.begin(); iter != instances.end(); iter++) {
		(*iter)->event(data);
	}
}

void
PR_CALLBACK Destructor(void * /* data */)
{
#if 0
    /*
     * We don't actually free the storage since it's actually allocated
     * on the stack. Normally, this would not be the case and this is
     * the opportunity to free whatever.
     */
    PR_Free(data);
#endif
}

/// \brief Return the MIME Type description for this plugin.
char*
NPP_GetMIMEDescription(void)
{
    return const_cast<char *>(MIME_TYPES_DESCRIPTION);
}

//
// general initialization and shutdown
//

/// \brief Initialize the plugin
///
/// This C++ function gets called once when the plugin is loaded,
/// regardless of how many instantiations there is actually playing
/// movies. So this is where all the one time only initialization
/// stuff goes.
NPError
NS_PluginInitialize()
{
    if ( plugInitialized )
    {
        return NPERR_NO_ERROR;
    }

    plugInitialized = TRUE;

	tuio_start(3333);

    return NPERR_NO_ERROR;
}

/// \brief Shutdown the plugin
///
/// This C++ function gets called once when the plugin is being
/// shutdown, regardless of how many instantiations actually are
/// playing movies. So this is where all the one time only
/// shutdown stuff goes.
void
NS_PluginShutdown()
{
#if 0
    if (!plugInitialized)
    {
#if GNASH_PLUGIN_DEBUG > 1
        std::cout << "Plugin already shut down" << std::endl;
#endif
        return;
    }

    plugInitialized = FALSE;
#endif

	tuio_stop();
}



/// \brief Retrieve values from the plugin for the Browser
///
/// This C++ function is called by the browser to get certain
/// information is needs from the plugin. This information is the
/// plugin name, a description, etc...
NPError
NS_PluginGetValue(NPPVariable aVariable, void *aValue)
{
    NPError err = NPERR_NO_ERROR;

    switch (aVariable)
    {
        case NPPVpluginNameString:
            *static_cast<const char **> (aValue) = PLUGIN_NAME;
            break;

        // This becomes the description field you see below the opening
        // text when you type about:plugins and in
        // navigator.plugins["Shockwave Flash"].description, used in
        // many flash version detection scripts.
        case NPPVpluginDescriptionString:
            *static_cast<const char **>(aValue) = PLUGIN_DESCRIPTION;
            break;

        case NPPVpluginNeedsXEmbed:

        case NPPVpluginTimerInterval:

        case NPPVpluginKeepLibraryInMemory:

        default:
            err = NPERR_INVALID_PARAM;
            break;
    }
    return err;
}

/// \brief construct our plugin instance object
///
/// This instantiates a new object via a C++ function used by the
/// browser.
nsPluginInstanceBase *
NS_NewPluginInstance(nsPluginCreateData * aCreateDataStruct)
{
    if(!aCreateDataStruct) return NULL;

    return new nsPluginInstance(aCreateDataStruct);
}

/// \brief destroy our plugin instance object
///
/// This destroys our instantiated object via a C++ function used by the
/// browser.
void
NS_DestroyPluginInstance(nsPluginInstanceBase* aPlugin)
{
    delete static_cast<nsPluginInstance *> (aPlugin);
}

//
// nsPluginInstance class implementation
//

/// \brief Constructor
nsPluginInstance::nsPluginInstance(nsPluginCreateData* data)
    :
    nsPluginInstanceBase(),
    _instance(data->instance),
	_port(3333),
	_callback("tuio_callback")
{
    for (size_t i=0, n=data->argc; i<n; ++i)
    {
        std::string name, val;

        if (data->argn[i])
        {
            name = data->argn[i];
        }

        if (data->argv[i])
        {
            val = data->argv[i];
        }

        else if ( ! strstr(name.c_str(), "callback") )
        {
            _callback = val;
        }

        else if ( ! strstr(name.c_str(), "port") )
        {
            _port = atoi(val.c_str());
        }
    }

	instances.insert(this);
}

/// \brief Destructor
nsPluginInstance::~nsPluginInstance()
{
	instances.erase(this);
}

/// \brief Initialize an instance of the plugin object
/// 
/// This methods initializes the plugin object, and is called for
/// every movie that gets played. This is where the movie playing
/// specific initialization goes.
NPBool
nsPluginInstance::init(NPWindow* aWindow)
{
	D("[ns] init");
    return TRUE;
}

/// \brief Shutdown an instantiated object
///
/// This shuts down an object, and is called for every movie that gets
/// played. This is where the movie playing specific shutdown code
/// goes.
void
nsPluginInstance::shut()
{
	D("[ns] shut");
}

NPError
nsPluginInstance::SetWindow(NPWindow* aWindow)
{
	D("[ns] SetWindow");

	if(!aWindow)
	{
		return NPERR_INVALID_PARAM;
	}

	return NPERR_NO_ERROR;
}

NPError
nsPluginInstance::GetValue(NPPVariable aVariable, void *aValue)
{
	return NS_PluginGetValue(aVariable, aValue);
}

/// \brief Write a status message
///
/// This writes a status message to the status line at the bottom of
/// the browser window and the console firefox was started from.
NPError
nsPluginInstance::WriteStatus(const char *msg) const
{
	NPN_Status(_instance, msg);
	std::cout << msg << std::endl;

	return NPERR_NO_ERROR;
}

NPError
nsPluginInstance::NewStream(NPMIMEType /*type*/, NPStream* stream,
                            NPBool /*seekable*/, uint16* /*stype*/)
{
	D("[ns] NewStream");
	return NPERR_NO_ERROR;
}

NPError
nsPluginInstance::DestroyStream(NPStream* /*stream*/, NPError /*reason*/)
{
	D("[ns] DestroyStream");
	return NPERR_NO_ERROR;
}

int32_t
nsPluginInstance::WriteReady(NPStream* /* stream */ )
{
	D("[ns] WriteReady");
	return 0x0fffffff;
}

int32_t
nsPluginInstance::Write(NPStream* /*stream*/, int32_t /*offset*/, int32_t len,
        void* buffer)
{
	D("[ns] Write: len=" << len);
	return len;
}

typedef struct {
	NPP instance;
	TuioEventData data;
} Event;

void test(void* ev)
{
	D("ev=" << ev);
	Event* event = (Event*)ev;
	D("event=" << event);
	std::stringstream ss;
	ss << "javascript:tuio_callback(";
	ss << event->data.type << ", ";
	ss << event->data.sid << ", ";
	ss << event->data.fid << ", ";
	ss << event->data.x << ", ";
	ss << event->data.y << ", ";
	ss << event->data.a << ");";
	NPN_GetURL(event->instance, ss.str().c_str(), "_self");

	delete event;
}

void nsPluginInstance::event(TuioEventData data)
{
	D("[event] callback: type=" << data.type
		<< ", sid=" << data.sid << ", fid=" << data.fid
		<< ", x=" << data.x << ", y=" << data.y << ", a=" << data.a);

	Event* ev = new Event();
	ev->instance = _instance;
	ev->data = data;

	NPN_PluginThreadAsyncCall(_instance, test, ev);
}

// Local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
