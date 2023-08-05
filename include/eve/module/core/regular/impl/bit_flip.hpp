//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/bit_xor.hpp>
#include <eve/module/core/regular/bit_shl.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/regular/all.hpp>

namespace eve::detail
{
  template<unsigned_value T, integral_value I>
  EVE_FORCEINLINE T
  bit_flip_(EVE_SUPPORTS(cpu_), T a, I i) noexcept
  {
    [[maybe_unused]] constexpr size_t S8 = sizeof(element_type_t<T>)*8;
    EVE_ASSERT(eve::all(i >= 0 && i < S8), "some index elements are out or range");
    return bit_xor(a, bit_shl(one(as(a)), i));
  }

  // Masked case
  template<conditional_expr C, unsigned_value T, integral_value I>
  EVE_FORCEINLINE auto
  bit_flip_(EVE_SUPPORTS(cpu_), C const& cond, T const& t, I const& i) noexcept
  {
    return mask_op(cond, eve::bit_flip, t, i);
  }
}
