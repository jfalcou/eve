//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/concept/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/arch/top_bits.hpp>

namespace eve::detail
{
  EVE_FORCEINLINE std::ptrdiff_t count_true_(EVE_SUPPORTS(cpu_), bool v) noexcept
  {
    return v ? 1 : 0;
  }

  template<value T>
  EVE_FORCEINLINE std::ptrdiff_t count_true_(EVE_SUPPORTS(cpu_), logical<T> v) noexcept
  {
    if constexpr(scalar_value<T>) return v.value() ? 1 : 0;
    else                          return count_true(eve::detail::top_bits{v});
  }

  template<simd_value T, relative_conditional_expr C>
  EVE_FORCEINLINE std::ptrdiff_t count_true_( EVE_SUPPORTS(cpu_)
                                            , C cond
                                            , logical<T> v
                                            ) noexcept
  {
    return count_true(top_bits{v,cond});
  }

  template<logical_simd_value Logical>
  EVE_FORCEINLINE std::ptrdiff_t count_true_( EVE_SUPPORTS(cpu_), top_bits<Logical> mmask ) noexcept
  {
    if constexpr ( !top_bits<Logical>::is_aggregated )
    {
      return std::popcount(mmask.as_int()) / top_bits<Logical>::bits_per_element;
    }
    else
    {
      return count_true(mmask.storage[0]) + count_true(mmask.storage[1]);
    }
  }
}
