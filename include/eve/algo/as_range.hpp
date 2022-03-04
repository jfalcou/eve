//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
namespace eve::algo
{
  template <typename I, typename S>
  struct as_range
  {
    I f;
    S l;

    as_range() = default;

    as_range(I f, S l) : f(f), l(l) {}

    using is_non_owning = void;

    I begin() const { return f; }
    S end  () const { return l; }
  };
}
