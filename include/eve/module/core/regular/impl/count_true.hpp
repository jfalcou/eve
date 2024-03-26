//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/top_bits.hpp>
#include <eve/concept/conditional.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/true.hpp>
#include <eve/module/core/regular/popcount.hpp>

namespace eve::detail
{

  template<callable_options O>
  EVE_FORCEINLINE constexpr ptrdiff_t
  count_true_(EVE_REQUIRES(cpu_), O const&, bool t) noexcept
  {
    return ptrdiff_t(t);
  }

  template<value T, callable_options O>
  EVE_FORCEINLINE constexpr ptrdiff_t
  count_true_(EVE_REQUIRES(cpu_), O const&, logical<T> t) noexcept
  {
    if constexpr( scalar_value<T> )
      return  ptrdiff_t(t.value());
    else
      return count_true(eve::top_bits {t});
  }

  template<logical_simd_value L, callable_options O>
  EVE_FORCEINLINE constexpr ptrdiff_t
  count_true_(EVE_REQUIRES(cpu_), O const&,  top_bits<L> mmask) noexcept
  {
    if constexpr( !top_bits<L>::is_aggregated )
      return std::popcount(mmask.as_int()) / top_bits<L>::bits_per_element;
    else
      return count_true(mmask.storage[0]) + count_true(mmask.storage[1]);
  }
}
