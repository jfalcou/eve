//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/concepts/eve_iterator.hpp>
#include <eve/algo/concepts/detail.hpp>

namespace eve::algo
{
  template <typename I, typename T>
  struct converting_iterator;

  struct convert_ {
    template <iterator I, typename T>
    auto operator()(I it, eve::as<T> tgt) const
    {
           if constexpr ( std::same_as<typename I::value_type, T>         )  return it;
      else if constexpr ( detail::instance_of<I, converting_iterator>     )  return operator()(it.base, tgt);
      else                                                                   return converting_iterator<I, T>{it};
    }
  } inline constexpr convert;
}
