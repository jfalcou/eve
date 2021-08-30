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
  struct preprocess_range_;

  template <typename I, typename S>
  struct range_pair
  {
    I f;
    S l;

    I begin() const { return f; }
    S end  () const { return l; }
  };

  template <typename I, typename S>
  range_pair(I f, S l) -> range_pair<I, S>;

  template <typename I, typename S>
  auto as_range(I f, S l) {
    return range_pair{f, l};
  }
}
