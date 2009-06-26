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
//

////////////////////////////////////////////////////////////
//
// Implementation of plugin entry points (NPP_*)
//
#include "pluginbase.h"

// here the plugin creates a plugin instance object which 
// will be associated with this newly created NPP instance and 
// will do all the necessary job
NPError NPP_New(NPMIMEType pluginType, NPP instance, uint16 mode, int16 argc, char* argn[], char* argv[], NPSavedData* saved)
{   
  if(instance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  NPError rv = NPERR_NO_ERROR;

  // create a new plugin instance object
  // initialization will be done when the associated window is ready
  nsPluginCreateData ds;
  
  ds.instance = instance;
  ds.type     = pluginType; 
  ds.mode     = mode; 
  ds.argc     = argc; 
  ds.argn     = argn; 
  ds.argv     = argv; 
  ds.saved    = saved;

  nsPluginInstanceBase * plugin = NS_NewPluginInstance(&ds);
  if(plugin == NULL)
    return NPERR_OUT_OF_MEMORY_ERROR;

  // associate the plugin instance object with NPP instance
  instance->pdata = (void *)plugin;
  return rv;
}

// here is the place to clean up and destroy the nsPluginInstance object
NPError NPP_Destroy (NPP instance, NPSavedData** /*save*/)
{
  if(instance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  NPError rv = NPERR_NO_ERROR;

  nsPluginInstanceBase * plugin = (nsPluginInstanceBase *)instance->pdata;
  if(plugin != NULL) {
    plugin->shut();
    NS_DestroyPluginInstance(plugin);
  }
  return rv;
}

// during this call we know when the plugin window is ready or
// is about to be destroyed so we can do some gui specific
// initialization and shutdown
NPError NPP_SetWindow (NPP instance, NPWindow* pNPWindow)
{    
  if(instance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  NPError rv = NPERR_NO_ERROR;

  if(pNPWindow == NULL)
    return NPERR_GENERIC_ERROR;

  nsPluginInstanceBase * plugin = (nsPluginInstanceBase *)instance->pdata;

  if(plugin == NULL) 
    return NPERR_GENERIC_ERROR;

  // window just created
  if(!plugin->isInitialized() && (pNPWindow->window != NULL)) { 
    if(!plugin->init(pNPWindow)) {
      NS_DestroyPluginInstance(plugin);
      return NPERR_MODULE_LOAD_FAILED_ERROR;
    }
  }

  // window goes away
  if((pNPWindow->window == NULL) && plugin->isInitialized())
    return plugin->SetWindow(pNPWindow);

  // window resized?
  if(plugin->isInitialized() && (pNPWindow->window != NULL))
    return plugin->SetWindow(pNPWindow);

  // this should not happen, nothing to do
  if((pNPWindow->window == NULL) && !plugin->isInitialized())
    return plugin->SetWindow(pNPWindow);

  return rv;
}

NPError NPP_NewStream(NPP instance, NPMIMEType type, NPStream* stream, NPBool seekable, uint16* stype)
{
  if(instance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  nsPluginInstanceBase * plugin = (nsPluginInstanceBase *)instance->pdata;
  if(plugin == NULL) 
    return NPERR_GENERIC_ERROR;

  NPError rv = plugin->NewStream(type, stream, seekable, stype);
  return rv;
}

int32 NPP_WriteReady (NPP instance, NPStream *stream)
{
  if(instance == NULL)
    return 0x0fffffff;

  nsPluginInstanceBase * plugin = (nsPluginInstanceBase *)instance->pdata;
  if(plugin == NULL) 
    return 0x0fffffff;

  int32 rv = plugin->WriteReady(stream);
  return rv;
}

int32 NPP_Write (NPP instance, NPStream *stream, int32 offset, int32 len, void *buffer)
{   
  if(instance == NULL)
    return len;

  nsPluginInstanceBase * plugin = (nsPluginInstanceBase *)instance->pdata;
  if(plugin == NULL) 
    return len;

  int32 rv = plugin->Write(stream, offset, len, buffer);
  return rv;
}

NPError NPP_DestroyStream (NPP instance, NPStream *stream, NPError reason)
{
  if(instance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  nsPluginInstanceBase * plugin = (nsPluginInstanceBase *)instance->pdata;
  if(plugin == NULL) 
    return NPERR_GENERIC_ERROR;

  NPError rv = plugin->DestroyStream(stream, reason);
  return rv;
}

void NPP_StreamAsFile (NPP instance, NPStream* stream, const char* fname)
{
  if(instance == NULL)
    return;

  nsPluginInstanceBase * plugin = (nsPluginInstanceBase *)instance->pdata;
  if(plugin == NULL) 
    return;

  plugin->StreamAsFile(stream, fname);
}

void NPP_Print (NPP instance, NPPrint* printInfo)
{
  if(instance == NULL)
    return;

  nsPluginInstanceBase * plugin = (nsPluginInstanceBase *)instance->pdata;
  if(plugin == NULL) 
    return;

  plugin->Print(printInfo);
}

void NPP_URLNotify(NPP instance, const char* url, NPReason reason, void* notifyData)
{
  if(instance == NULL)
    return;

  nsPluginInstanceBase * plugin = (nsPluginInstanceBase *)instance->pdata;
  if(plugin == NULL) 
    return;

  plugin->URLNotify(url, reason, notifyData);
}

NPError	NPP_GetValue(NPP instance, NPPVariable variable, void *value)
{
  if(instance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  nsPluginInstanceBase * plugin = (nsPluginInstanceBase *)instance->pdata;
  if(plugin == NULL) 
    return NPERR_GENERIC_ERROR;

  NPError rv = plugin->GetValue(variable, value);
  return rv;
}

NPError NPP_SetValue(NPP instance, NPNVariable variable, void *value)
{
  if(instance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  nsPluginInstanceBase * plugin = (nsPluginInstanceBase *)instance->pdata;
  if(plugin == NULL) 
    return NPERR_GENERIC_ERROR;

  NPError rv = plugin->SetValue(variable, value);
  return rv;
}

int16	NPP_HandleEvent(NPP instance, void* event)
{
  if(instance == NULL)
    return 0;

  nsPluginInstanceBase * plugin = (nsPluginInstanceBase *)instance->pdata;
  if(plugin == NULL) 
    return 0;

  uint16 rv = plugin->HandleEvent(event);
  return rv;
}

// FIXME /**************************************************/
// FIXME /*                                                */
// FIXME /*                     Mac                        */
// FIXME /*                                                */
// FIXME /**************************************************/
// FIXME 
// FIXME // Mac needs these wrappers, see npplat.h for more info
// FIXME 
// FIXME #ifdef XP_MAC
// FIXME 
// FIXME NPError	Private_New(NPMIMEType pluginType, NPP instance, uint16 mode, int16 argc, char* argn[], char* argv[], NPSavedData* saved)
// FIXME {
// FIXME   NPError rv = NPP_New(pluginType, instance, mode, argc, argn, argv, saved);
// FIXME   return rv;	
// FIXME }
// FIXME 
// FIXME NPError Private_Destroy(NPP instance, NPSavedData** save)
// FIXME {
// FIXME   NPError rv = NPP_Destroy(instance, save);
// FIXME   return rv;
// FIXME }
// FIXME 
// FIXME NPError Private_SetWindow(NPP instance, NPWindow* window)
// FIXME {
// FIXME   NPError rv = NPP_SetWindow(instance, window);
// FIXME   return rv;
// FIXME }
// FIXME 
// FIXME NPError Private_NewStream(NPP instance, NPMIMEType type, NPStream* stream, NPBool seekable, uint16* stype)
// FIXME {
// FIXME   NPError rv = NPP_NewStream(instance, type, stream, seekable, stype);
// FIXME   return rv;
// FIXME }
// FIXME 
// FIXME int32 Private_WriteReady(NPP instance, NPStream* stream)
// FIXME {
// FIXME   int32 rv = NPP_WriteReady(instance, stream);
// FIXME   return rv;
// FIXME }
// FIXME 
// FIXME int32 Private_Write(NPP instance, NPStream* stream, int32 offset, int32 len, void* buffer)
// FIXME {
// FIXME   int32 rv = NPP_Write(instance, stream, offset, len, buffer);
// FIXME   return rv;
// FIXME }
// FIXME 
// FIXME void Private_StreamAsFile(NPP instance, NPStream* stream, const char* fname)
// FIXME {
// FIXME   NPP_StreamAsFile(instance, stream, fname);
// FIXME }
// FIXME 
// FIXME 
// FIXME NPError Private_DestroyStream(NPP instance, NPStream* stream, NPError reason)
// FIXME {
// FIXME   NPError rv = NPP_DestroyStream(instance, stream, reason);
// FIXME   return rv;
// FIXME }
// FIXME 
// FIXME int16 Private_HandleEvent(NPP instance, void* event)
// FIXME {
// FIXME   int16 rv = NPP_HandleEvent(instance, event);
// FIXME   return rv;
// FIXME }
// FIXME 
// FIXME void Private_Print(NPP instance, NPPrint* platformPrint)
// FIXME {
// FIXME   NPP_Print(instance, platformPrint);
// FIXME }
// FIXME 
// FIXME void Private_URLNotify(NPP instance, const char* url, NPReason reason, void* notifyData)
// FIXME {
// FIXME   NPP_URLNotify(instance, url, reason, notifyData);
// FIXME }
// FIXME 
// FIXME jref Private_GetJavaClass(void)
// FIXME {
// FIXME   return NULL;
// FIXME }
// FIXME 
// FIXME NPError Private_GetValue(NPP instance, NPPVariable variable, void *result)
// FIXME {
// FIXME   NPError rv = NPP_GetValue(instance, variable, result);
// FIXME   return rv;
// FIXME }
// FIXME 
// FIXME NPError Private_SetValue(NPP instance, NPNVariable variable, void *value)
// FIXME {
// FIXME   NPError rv = NPP_SetValue(instance, variable, value);
// FIXME   return rv;
// FIXME }
// FIXME 
// FIXME #endif //XP_MAC
