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

#ifndef ADAPTER_NPAPI_H_
#define ADAPTER_NPAPI_H_

#include "../npapi/npfunctions.h"

#include <string>
#include "adapter.h"

class NPAPIAdapter : public Adapter {
public:
  NPAPIAdapter(const NPNetscapeFuncs* browser,
               const void* plugin_instance,
               std::string callback);
  ~NPAPIAdapter();

  virtual void Init();
  virtual void Destroy();

  virtual void Invoke(TuioEvent event);

  std::string get_callback() {
    return callback_;
  }

private:
  const NPNetscapeFuncs* browser_;
  const void* plugin_instance_;
  std::string callback_;
};

#endif
