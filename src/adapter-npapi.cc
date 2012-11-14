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

#include <sstream>

#include "debug.h"

struct Data {
  const NPNetscapeFuncs* browser;
  const void* plugin_instance;
  const TuioEvent event;

  Data(const NPNetscapeFuncs* browser, const void* plugin_instance,
       const TuioEvent event)
      : browser(browser), plugin_instance(plugin_instance), event(event) {
  }
};

static void call_javascript(void* param) {
  Data* data = (Data*)param;

  D("AsyncCaller::invokeJavascript");

  std::stringstream url;
	url << "javascript:tuio_callback(";
	url << data->event.type << ", ";
	url << data->event.sid << ", ";
	url << data->event.fid << ", ";
	url << data->event.x << ", ";
	url << data->event.y << ", ";
	url << data->event.a << ");";
  D("url: %s", url.str().c_str());

  data->browser->geturl(
    (NPP)data->plugin_instance, url.str().c_str(), "_self");

  delete data;
}

NPAPIAdapter::NPAPIAdapter(const NPNetscapeFuncs* browser,
                           const void* plugin_instance,
                           const char* callback)
    : browser_(browser), plugin_instance_(plugin_instance),
      callback_(callback) {
}

NPAPIAdapter::~NPAPIAdapter() {
}

void NPAPIAdapter::Init() {
}

void NPAPIAdapter::Destroy() {
}

void NPAPIAdapter::Invoke(TuioEvent event) {
  Data* data = new Data(browser_, plugin_instance_, event);
  browser_->pluginthreadasynccall(
    (NPP)plugin_instance_, call_javascript, data);
}

