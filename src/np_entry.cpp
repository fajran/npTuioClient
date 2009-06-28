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

//////////////////////////////////////////////////////////////
//
// Main plugin entry point implementation -- exports from the 
// plugin library
//
#include "npplat.h"
#include "pluginbase.h"

NPNetscapeFuncs NPNFuncs;

#ifdef XP_MAC
void OSCALL NP_Shutdown()
{
  NS_PluginShutdown();
}
#else
NPError OSCALL NP_Shutdown()
{
  NS_PluginShutdown();
  return NPERR_NO_ERROR;
}
#endif

static NPError fillPluginFunctionTable(NPPluginFuncs* aNPPFuncs)
{
  if(aNPPFuncs == NULL)
    return NPERR_INVALID_FUNCTABLE_ERROR;

  // Set up the plugin function table that Netscape will use to
  // call us. Netscape needs to know about our version and size   
  // and have a UniversalProcPointer for every function we implement.

  aNPPFuncs->version       = (NP_VERSION_MAJOR << 8) | NP_VERSION_MINOR;
#ifdef XP_MAC
  aNPPFuncs->newp          = NewNPP_NewProc(Private_New);
  aNPPFuncs->destroy       = NewNPP_DestroyProc(Private_Destroy);
  aNPPFuncs->setwindow     = NewNPP_SetWindowProc(Private_SetWindow);
  aNPPFuncs->newstream     = NewNPP_NewStreamProc(Private_NewStream);
  aNPPFuncs->destroystream = NewNPP_DestroyStreamProc(Private_DestroyStream);
  aNPPFuncs->asfile        = NewNPP_StreamAsFileProc(Private_StreamAsFile);
  aNPPFuncs->writeready    = NewNPP_WriteReadyProc(Private_WriteReady);
  aNPPFuncs->write         = NewNPP_WriteProc(Private_Write);
  aNPPFuncs->print         = NewNPP_PrintProc(Private_Print);
  aNPPFuncs->event         = NewNPP_HandleEventProc(Private_HandleEvent);	
  aNPPFuncs->urlnotify     = NewNPP_URLNotifyProc(Private_URLNotify);			
  aNPPFuncs->getvalue      = NewNPP_GetValueProc(Private_GetValue);
  aNPPFuncs->setvalue      = NewNPP_SetValueProc(Private_SetValue);
#else
  aNPPFuncs->newp          = NPP_New;
  aNPPFuncs->destroy       = NPP_Destroy;
  aNPPFuncs->setwindow     = NPP_SetWindow;
  aNPPFuncs->newstream     = NPP_NewStream;
  aNPPFuncs->destroystream = NPP_DestroyStream;
  aNPPFuncs->asfile        = NPP_StreamAsFile;
  aNPPFuncs->writeready    = NPP_WriteReady;
  aNPPFuncs->write         = NPP_Write;
  aNPPFuncs->print         = NPP_Print;
  aNPPFuncs->event         = NPP_HandleEvent;
  aNPPFuncs->urlnotify     = NPP_URLNotify;
  aNPPFuncs->getvalue      = NPP_GetValue;
  aNPPFuncs->setvalue      = NPP_SetValue;
#endif
#ifdef OJI
  aNPPFuncs->javaClass     = NULL;
#endif

  return NPERR_NO_ERROR;
}

static NPError fillNetscapeFunctionTable(NPNetscapeFuncs* aNPNFuncs)
{
  int i = 0, n;

  if(aNPNFuncs == NULL)
    return NPERR_INVALID_FUNCTABLE_ERROR;

  if(HIBYTE(aNPNFuncs->version) > NP_VERSION_MAJOR)
    return NPERR_INCOMPATIBLE_VERSION_ERROR;

#if 0
  if(aNPNFuncs->size < sizeof(NPNetscapeFuncs))
    return NPERR_INVALID_FUNCTABLE_ERROR;
#endif

  // Number of function pointers in aNPNFuncs.
  n = (aNPNFuncs->size - (2 * sizeof(uint16))) / sizeof(void *);

  NPNFuncs.size             = aNPNFuncs->size;
  NPNFuncs.version          = aNPNFuncs->version;

  /*
   * BEWARE!  The following is order-sensitive and needs to be in the
   * same order as the structure definition from npupp.h.
   */

  if (++i <= n) NPNFuncs.geturl = aNPNFuncs->geturl;
  if (++i <= n) NPNFuncs.posturl = aNPNFuncs->posturl;
  if (++i <= n) NPNFuncs.requestread = aNPNFuncs->requestread;
  if (++i <= n) NPNFuncs.newstream = aNPNFuncs->newstream;
  if (++i <= n) NPNFuncs.write = aNPNFuncs->write;
  if (++i <= n) NPNFuncs.destroystream = aNPNFuncs->destroystream;
  if (++i <= n) NPNFuncs.status = aNPNFuncs->status;
  if (++i <= n) NPNFuncs.uagent = aNPNFuncs->uagent;
  if (++i <= n) NPNFuncs.memalloc = aNPNFuncs->memalloc;
  if (++i <= n) NPNFuncs.memfree = aNPNFuncs->memfree;
  if (++i <= n) NPNFuncs.memflush = aNPNFuncs->memflush;
  if (++i <= n) NPNFuncs.reloadplugins = aNPNFuncs->reloadplugins;
  if (++i <= n) NPNFuncs.getJavaEnv = aNPNFuncs->getJavaEnv;
  if (++i <= n) NPNFuncs.getJavaPeer = aNPNFuncs->getJavaPeer;
  if (++i <= n) NPNFuncs.geturlnotify = aNPNFuncs->geturlnotify;
  if (++i <= n) NPNFuncs.posturlnotify = aNPNFuncs->posturlnotify;
  if (++i <= n) NPNFuncs.getvalue = aNPNFuncs->getvalue;
  if (++i <= n) NPNFuncs.setvalue = aNPNFuncs->setvalue;
  if (++i <= n) NPNFuncs.invalidaterect = aNPNFuncs->invalidaterect;
  if (++i <= n) NPNFuncs.invalidateregion = aNPNFuncs->invalidateregion;
  if (++i <= n) NPNFuncs.forceredraw = aNPNFuncs->forceredraw;
  if (++i <= n) NPNFuncs.getstringidentifier = aNPNFuncs->getstringidentifier;
  if (++i <= n) NPNFuncs.getstringidentifiers = aNPNFuncs->getstringidentifiers;
  if (++i <= n) NPNFuncs.getintidentifier = aNPNFuncs->getintidentifier;
  if (++i <= n) NPNFuncs.identifierisstring = aNPNFuncs->identifierisstring;
  if (++i <= n) NPNFuncs.utf8fromidentifier = aNPNFuncs->utf8fromidentifier;
  if (++i <= n) NPNFuncs.intfromidentifier = aNPNFuncs->intfromidentifier;
  if (++i <= n) NPNFuncs.createobject = aNPNFuncs->createobject;
  if (++i <= n) NPNFuncs.retainobject = aNPNFuncs->retainobject;
  if (++i <= n) NPNFuncs.releaseobject = aNPNFuncs->releaseobject;
  if (++i <= n) NPNFuncs.invoke = aNPNFuncs->invoke;
  if (++i <= n) NPNFuncs.invokeDefault = aNPNFuncs->invokeDefault;
  if (++i <= n) NPNFuncs.evaluate = aNPNFuncs->evaluate;
  if (++i <= n) NPNFuncs.getproperty = aNPNFuncs->getproperty;
  if (++i <= n) NPNFuncs.setproperty = aNPNFuncs->setproperty;
  if (++i <= n) NPNFuncs.removeproperty = aNPNFuncs->removeproperty;
  if (++i <= n) NPNFuncs.hasproperty = aNPNFuncs->hasproperty;
  if (++i <= n) NPNFuncs.hasmethod = aNPNFuncs->hasmethod;
  if (++i <= n) NPNFuncs.releasevariantvalue = aNPNFuncs->releasevariantvalue;
  if (++i <= n) NPNFuncs.setexception = aNPNFuncs->setexception;
  if (++i <= n) NPNFuncs.pushpopupsenabledstate = aNPNFuncs->pushpopupsenabledstate;
  if (++i <= n) NPNFuncs.poppopupsenabledstate = aNPNFuncs->poppopupsenabledstate;
  if (++i <= n) NPNFuncs.enumerate = aNPNFuncs->enumerate;
  if (++i <= n) NPNFuncs.pluginthreadasynccall = aNPNFuncs->pluginthreadasynccall;
  if (++i <= n) NPNFuncs.construct = aNPNFuncs->construct;

  return NPERR_NO_ERROR;
}

//
// Some exports are different on different platforms
//

/**************************************************/
/*                                                */
/*                   Windows                      */
/*                                                */
/**************************************************/
#ifdef XP_WIN

NPError OSCALL NP_Initialize(NPNetscapeFuncs* aNPNFuncs)
{
  /*
   * N.B.  On Firefox 2.0.0.12/WinXP, aNPNFuncs->size is 172 while
   * sizeof(NPNetscapeFuncs) is 184.  However, npgnash.dll continues to
   * work fine even though NPNFuncs isn't populated (!), and as a matter
   * of fact, Firefox seems to ignore the NPERR_INVALID_FUNCTABLE_ERROR
   * return from NP_Initialize and continues to load and execute
   * npgnash.dll, anyway.  Therefore, we should continue and execute
   * NS_PluginInitialize anyway, too.
   */

  NPError rv = fillNetscapeFunctionTable(aNPNFuncs);
#if 0
  if(rv != NPERR_NO_ERROR)
    return rv;
#endif
  NPError rv2 = NS_PluginInitialize();

  return rv2 != NPERR_NO_ERROR ? rv2 : rv;
}

NPError OSCALL NP_GetEntryPoints(NPPluginFuncs* aNPPFuncs)
{
  return fillPluginFunctionTable(aNPPFuncs);
}

#endif //XP_WIN

/**************************************************/
/*                                                */
/*                    Unix                        */
/*                                                */
/**************************************************/
#ifdef XP_UNIX

#ifdef XP_MAC
NPError NP_Initialize(NPNetscapeFuncs* aNPNFuncs)
#else
NPError NP_Initialize(NPNetscapeFuncs* aNPNFuncs, NPPluginFuncs* aNPPFuncs)
#endif
{
  NPError rv = fillNetscapeFunctionTable(aNPNFuncs);
  if(rv != NPERR_NO_ERROR)
    return rv;

#ifndef XP_MAC
  rv = fillPluginFunctionTable(aNPPFuncs);
  if(rv != NPERR_NO_ERROR)
    return rv;
#endif

  return NS_PluginInitialize();
}

char * NP_GetMIMEDescription(void)
{
  return NPP_GetMIMEDescription();
}

NPError NP_GetValue(void* /*future*/, NPPVariable aVariable, void *aValue)
{
  return NS_PluginGetValue(aVariable, aValue);
}

#endif //XP_UNIX

/**************************************************/
/*                                                */
/*                     Mac                        */
/*                                                */
/**************************************************/
#ifdef XP_MAC

NPError OSCALL NP_GetEntryPoints(NPPluginFuncs* aNPPFuncs)
{
  return fillPluginFunctionTable(aNPPFuncs);
}

NPError Private_Initialize(void)
{
  NPError rv = NS_PluginInitialize();
  return rv;
}

void Private_Shutdown(void)
{
  NS_PluginShutdown();
//  __destroy_global_chain();
}

#endif //XP_MAC
