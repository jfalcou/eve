//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <concepts>

namespace eve::algo
{
  template <typename T>
  using unaligned_t = decltype(std::declval<T>().unaligned());

  // Do the other way around to the normal one, otherwise there is a compilation issue.
  template <typename T>
  struct unaligned
  {
    using type = unaligned_t<T>;
  };


  template <typename T, typename U>
  concept same_unaligned_iterator = std::same_as<unaligned_t<T>, unaligned_t<U>>;
}
