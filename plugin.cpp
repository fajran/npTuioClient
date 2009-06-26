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

#define MIME_TYPES_HANDLED  "application/x-tuio"
// The name must be this value to get flash movies that check the
// plugin version to load.
#define PLUGIN_NAME    "TUIO Client"
#define MIME_TYPES_DESCRIPTION  MIME_TYPES_HANDLED":tuio:"PLUGIN_NAME

#define PLUGIN_DESCRIPTION "TUIO Client plugin"

extern NPNetscapeFuncs NPNFuncs;

NPBool plugInitialized = FALSE;

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
	_host("localhost"),
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

        if ( ! strcasecmp(name.c_str(), "host") )
        {
            _host = val;
        }

        else if ( ! strcasecmp(name.c_str(), "callback") )
        {
            _callback = val;
        }

        else if ( ! strcasecmp(name.c_str(), "port") )
        {
            _port = atoi(val.c_str());
        }
    }

}

/// \brief Destructor
nsPluginInstance::~nsPluginInstance()
{
}

/// \brief Initialize an instance of the plugin object
/// 
/// This methods initializes the plugin object, and is called for
/// every movie that gets played. This is where the movie playing
/// specific initialization goes.
NPBool
nsPluginInstance::init(NPWindow* aWindow)
{
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
nsPluginInstance::WriteStatus(char *msg) const
{
    NPN_Status(_instance, msg);
    std::cout << msg << std::endl;

    return NPERR_NO_ERROR;
}

// Local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
