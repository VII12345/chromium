// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/frame/navigator_concurrent_hardware.h"
#include "base/command_line.h"
#include "base/system/sys_info.h"

namespace blink {

unsigned NavigatorConcurrentHardware::hardwareConcurrency() const {
  base::CommandLine* base_command_line = base::CommandLine::ForCurrentProcess();
  int tmp;

  if (base_command_line->HasSwitch("fingerprint_cpu")) {
    std::istringstream(
        base_command_line->GetSwitchValueASCII("fingerprint_cpu")) >>
        tmp;
    return tmp;
  } 
  else
    return static_cast<unsigned>(base::SysInfo::NumberOfProcessors());
}

}  // namespace blink
