//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

namespace eve::algo
{
  template <typename I, typename S>
  auto as_range(I f, S l) {
    struct {
      I f;
      S l;

      I begin() const { return f; }
      S end  () const { return l; }

    } res{f, l};
    return res;
  }
}
