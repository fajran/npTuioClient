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

#include "plugin.h"

#include "../npapi/npapi.h"
#include "../npapi/npfunctions.h"

#define PLUGIN_NAME             "TUIO Client"
#define MIME_TYPES_HANDLED      "application/x-tuio"
#define MIME_TYPES_DESCRIPTION  MIME_TYPES_HANDLED":tuio:"PLUGIN_NAME
#define PLUGIN_DESCRIPTION      "TUIO Client plugin"
#define PLUGIN_VERSION          "0.5"

#ifdef __cplusplus
extern "C" {
#endif

NP_EXPORT(NPError) NP_Initialize(NPNetscapeFuncs* bFuncs,
                                 NPPluginFuncs* pFuncs) {
  pFuncs->newp = NPP_New;
  pFuncs->destroy = NPP_Destroy;
  pFuncs->setwindow = NPP_SetWindow;
  pFuncs->newstream = NPP_NewStream;
  pFuncs->destroystream = NPP_DestroyStream;
  pFuncs->asfile = NPP_StreamAsFile;
  pFuncs->writeready = NPP_WriteReady;
  pFuncs->write = NPP_Write;
  pFuncs->print = NPP_Print;
  pFuncs->event = NPP_HandleEvent;
  pFuncs->urlnotify = NPP_URLNotify;
  pFuncs->getvalue = NPP_GetValue;
  pFuncs->setvalue = NPP_SetValue;

  return NPERR_NO_ERROR;
}

NP_EXPORT(char*) NP_GetPluginVersion() {
  return (char*)PLUGIN_VERSION;
}

NP_EXPORT(const char*) NP_GetMIMEDescription() {
  return MIME_TYPES_DESCRIPTION;
}

NP_EXPORT(NPError) NP_GetValue(void* future, NPPVariable variable,
                               void* value) {
  switch (variable) {
    case NPPVpluginNameString:
      *((char**)value) = (char*)PLUGIN_NAME;
      break;
    case NPPVpluginDescriptionString:
      *((char**)value) = (char*)PLUGIN_DESCRIPTION;
      break;
    case NPPVpluginNeedsXEmbed:
      *(int*)value = true;
      break;
    default:
      return NPERR_INVALID_PARAM;
      break;
  }
  return NPERR_NO_ERROR;
}

NP_EXPORT(NPError) NP_Shutdown() {
  return NPERR_NO_ERROR;
}

NPError NPP_New(NPMIMEType pluginType, NPP instance, uint16_t mode,
                int16_t argc, char* argn[], char* argv[],
                NPSavedData* saved) {
  // TODO instantiate instances
  //      if malloc fails, returns NPERR_OUT_OF_MEMORY_ERROR
  //      if error, returns NPERR_GENERIC_ERROR
  return NPERR_NO_ERROR;
}

NPError NPP_Destroy(NPP instance, NPSavedData** save) {
  // TODO free up memory
  return NPERR_NO_ERROR;
}

NPError NPP_SetWindow(NPP instance, NPWindow* window) {
  return NPERR_NO_ERROR;
}

NPError NPP_NewStream(NPP instance, NPMIMEType type, NPStream* stream,
                      NPBool seekable, uint16_t* stype) {
  return NPERR_GENERIC_ERROR;
}

NPError NPP_DestroyStream(NPP instance, NPStream* stream, NPReason reason) {
  return NPERR_GENERIC_ERROR;
}

int32_t NPP_WriteReady(NPP instance, NPStream* stream) {
  return 0;
}

int32_t NPP_Write(NPP instance, NPStream* stream, int32_t offset, int32_t len,
                  void* buffer) {
  return 0;
}

void NPP_StreamAsFile(NPP instance, NPStream* stream, const char* fname) {

}

void NPP_Print(NPP instance, NPPrint* platformPrint) {

}

int16_t NPP_HandleEvent(NPP instance, void* event) {
  return 0;
}

void NPP_URLNotify(NPP instance, const char* URL, NPReason reason,
                   void* notifyData) {
}

NPError NPP_GetValue(NPP instance, NPPVariable variable, void* value) {
  switch (variable) {
    case NPPVpluginNameString:
      *((char**)value) = (char*)PLUGIN_NAME;
      break;
    case NPPVpluginDescriptionString:
      *((char**)value) = (char*)PLUGIN_DESCRIPTION;
      break;
    case NPPVpluginNeedsXEmbed:
      *(int*)value = true;
      break;
    default:
      return NPERR_INVALID_PARAM;
      break;
  }
  return NPERR_NO_ERROR;
}

NPError NPP_SetValue(NPP instance, NPNVariable variable, void* value) {
  return NPERR_GENERIC_ERROR;
}

#ifdef __cplusplus
}
#endif

