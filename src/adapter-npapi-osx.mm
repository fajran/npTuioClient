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

#include "adapter-npapi.h"

#include "../npapi/npapi.h"
#include "../npapi/npfunctions.h"

#include <sstream>

#include "debug.h"

@interface AsyncCaller : NSObject
{
  NPNetscapeFuncs* browser_;
  void* pluginInstance_;
  char* callback_;
  TuioEvent event_;
}

- (id)initWithBrowser:(NPNetscapeFuncs*)browser
       pluginInstance:(const void*)pluginInstance
             callback:(const char*)callback
         andTuioEvent:(TuioEvent)event;

- (void)invoke;

@end

@implementation AsyncCaller

- (id)initWithBrowser:(NPNetscapeFuncs*)browser
       pluginInstance:(const void*)pluginInstance
             callback:(const char*)callback
         andTuioEvent:(TuioEvent)event {
  id res = [super init];

  browser_ = browser;
  pluginInstance_ = (void*)pluginInstance;
  callback_ = (char*)callback;
  event_ = event;

  return res;
}

- (void)invoke {
  D("AsyncCaller::invoke");
  [self performSelectorOnMainThread:@selector(invokeJavascript)
                         withObject:nil
                      waitUntilDone:NO];
}

- (void)invokeJavascript {
  D("AsyncCaller::invokeJavascript");

  std::stringstream url;
	url << "javascript:" << callback_ << "(";
	url << event_.type << ", ";
	url << event_.sid << ", ";
	url << event_.fid << ", ";
	url << event_.x << ", ";
	url << event_.y << ", ";
	url << event_.a << ");";
  D("url: %s", url.str().c_str());

  browser_->geturl((NPP)pluginInstance_, url.str().c_str(), "_self");

  [self release];
}

@end


NPAPIAdapter::NPAPIAdapter(const NPNetscapeFuncs* browser,
                           const void* plugin_instance,
                           const char* callback)
  : browser_(browser), plugin_instance_(plugin_instance), callback_(callback) {
}

NPAPIAdapter::~NPAPIAdapter() {
}

void NPAPIAdapter::Init() {
}

void NPAPIAdapter::Destroy() {
}

void NPAPIAdapter::Invoke(TuioEvent event) {
  D("NPAPIAdapter::Invoke");

  AsyncCaller* caller = [[AsyncCaller alloc]
                         initWithBrowser:(NPNetscapeFuncs*)browser_
                          pluginInstance:plugin_instance_
                                callback:callback_
                            andTuioEvent:event];
  [caller invoke];
}
