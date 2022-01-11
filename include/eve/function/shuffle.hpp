/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/real/core/detail/basic_shuffle.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(shuffle_, shuffle);
}


#include <eve/module/real/core/detail/generic/find_optimized_shuffle_pattern.hpp>

namespace eve::detail
{
  template<simd_value T, std::ptrdiff_t... I>
  EVE_FORCEINLINE constexpr auto shuffle_(EVE_SUPPORTS(cpu_), T v, pattern_t<I...>) noexcept
  requires(pattern_t<I...>{}.validate(T::size()))
  {
    constexpr auto shuffler = detail::find_optimized_shuffle_pattern<T::size(),I...>();
    return shuffler(v);
  }

  template<simd_value T, typename F>
  EVE_FORCEINLINE constexpr auto shuffle_(EVE_SUPPORTS(cpu_), T v, as_pattern<F> p) noexcept
  {
    return shuffle(v, fix_pattern<T::size()>(p));
  }
}

