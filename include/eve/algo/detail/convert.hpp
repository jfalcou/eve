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
  template <typename I, typename T>
  struct converting_iterator;

  struct convert_ {
    template <typename Wrapped, typename T>
    auto no_tagged_dispatch(Wrapped&& wrapped, eve::as<T> tgt) const;

    template <typename Wrapped, typename T>
    auto operator()(Wrapped&& wrapped, eve::as<T> tgt) const;
  } inline constexpr convert;

  namespace detail
  {
    template <typename Self, typename T>
    auto convert_zipped(Self self, eve::as<T> tgt);
  }
}
