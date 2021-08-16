//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once


#include <eve/memory/aligned_ptr.hpp>

#include <type_traits>

namespace eve::algo {

struct
{
  template <typename T, typename N>
  T* operator()(aligned_ptr<T, N> p) const
  {
    return p.get();
  }

  template <typename I>
  auto operator()(I i) const
  {
    if constexpr (std::contiguous_iterator<I>) return i;
    else                                       return i.unaligned();
  }
} inline constexpr unalign;

template <typename T>
using unaligned_t = decltype(unalign(std::declval<T>()));

// Do the other way around to the normal one, otherwise there is a compilation issue.
template <typename T>
struct unaligned
{
  using type = unaligned_t<T>;
};

}
