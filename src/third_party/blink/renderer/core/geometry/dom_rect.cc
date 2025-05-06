// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/geometry/dom_rect.h"

#include "third_party/blink/renderer/bindings/core/v8/v8_dom_rect_init.h"
#include "third_party/blink/renderer/platform/wtf/math_extras.h"
#include "ui/gfx/geometry/rect.h"
#include "ui/gfx/geometry/rect_conversions.h"
#include "ui/gfx/geometry/rect_f.h"
#include "base/command_line.h"
namespace blink {

DOMRect* DOMRect::Create(double x, double y, double width, double height) {
  return MakeGarbageCollected<DOMRect>(x, y, width, height);
}

//DOMRect* DOMRect::FromRectF(const gfx::RectF& rect) {
//  return MakeGarbageCollected<DOMRect>(rect.x(), rect.y(), rect.width(),
//                                       rect.height());
//}
DOMRect* DOMRect::FromRectF(const gfx::RectF& rect) {
  base::CommandLine* base_command_line = base::CommandLine::ForCurrentProcess();
  int seed;
  if (base_command_line->HasSwitch("fingerprint_client_rect")) {
    std::istringstream(
        base_command_line->GetSwitchValueASCII("fingerprint_client_rect")) >>
        seed;
  } else {
     return MakeGarbageCollected<DOMRect>(rect.x(), rect.y(), rect.width(),
     rect.height());
  }

  float new_width;
  float new_height;
  if (rect.x() > 0) {
    new_width = rect.width() + (seed % 103 / 100000.0);
    new_height = rect.height() + (seed % 97 / 100000.0);
  } else {
    new_width = rect.width();
    new_height = rect.height();
  }

  return MakeGarbageCollected<DOMRect>(rect.x(), rect.y(), new_width,
                                       new_height);
  // return MakeGarbageCollected<DOMRect>(rect.x(), rect.y(), rect.width(),
  // rect.height());
}

DOMRect* DOMRect::fromRect(const DOMRectInit* other) {
  return MakeGarbageCollected<DOMRect>(other->x(), other->y(), other->width(),
                                       other->height());
}

DOMRect::DOMRect(double x, double y, double width, double height)
    : DOMRectReadOnly(x, y, width, height) {}

gfx::Rect DOMRect::ToEnclosingRect() const {
  return gfx::ToEnclosingRect(
      gfx::RectF(ClampTo<float>(x()), ClampTo<float>(y()),
                 ClampTo<float>(width()), ClampTo<float>(height())));
}

}  // namespace blink
