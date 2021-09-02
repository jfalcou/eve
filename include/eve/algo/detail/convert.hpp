//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/traits.hpp>

namespace eve::algo
{
  struct convert_ {
    template <typename Wrapped, typename T>
    auto operator()(Wrapped&& wrapped, eve::as<T> tgt) const;

  } inline constexpr convert;
}
