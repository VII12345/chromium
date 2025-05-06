// Copyright 2019 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/frame/navigator_ua.h"
#include "base/command_line.h"
#include "base/compiler_specific.h"
#include "third_party/blink/public/common/user_agent/user_agent_metadata.h"
#include "third_party/blink/renderer/core/frame/navigator_ua_data.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

namespace blink {

NavigatorUAData* NavigatorUA::userAgentData() {
  NavigatorUAData* ua_data =
      MakeGarbageCollected<NavigatorUAData>(GetUAExecutionContext());

  UserAgentMetadata metadata = GetUserAgentMetadata();
  ua_data->SetBrandVersionList(metadata.brand_version_list);
  ua_data->SetMobile(metadata.mobile);
  //ua_data->SetPlatform(String::FromUTF8(metadata.platform),
  //                     String::FromUTF8(metadata.platform_version));

  base::CommandLine* base_command_line = base::CommandLine::ForCurrentProcess();

  int seed;
  if (base_command_line->HasSwitch("fingerprint_windows")) {
    std::istringstream(
        base_command_line->GetSwitchValueASCII("fingerprint_windows")) >>
        seed;
    int platfrom_v = 7;
    platfrom_v = seed % 7 + 10;
    ua_data->SetPlatform(String::FromUTF8(metadata.platform),
                         String::FromUTF8(std::to_string(platfrom_v) + ".0.0"));
  }
  else{
      ua_data->SetPlatform(String::FromUTF8(metadata.platform),
          String::FromUTF8(metadata.platform_version));
  }






  ua_data->SetArchitecture(String::FromUTF8(metadata.architecture));
  ua_data->SetModel(String::FromUTF8(metadata.model));
  ua_data->SetUAFullVersion(String::FromUTF8(metadata.full_version));
  ua_data->SetBitness(String::FromUTF8(metadata.bitness));
  ua_data->SetFullVersionList(metadata.brand_full_version_list);
  ua_data->SetWoW64(metadata.wow64);
  Vector<String> form_factors;
  form_factors.reserve(
      base::checked_cast<wtf_size_t>(metadata.form_factors.size()));
  for (auto& ff : metadata.form_factors) {
    form_factors.push_back(String::FromUTF8(ff));
  }
  ua_data->SetFormFactors(std::move(form_factors));

  return ua_data;
}

}  // namespace blink
