//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/detail/top_bits.hpp>

namespace eve::detail
{
  //================================================================================================
  // X86 implementation
  //================================================================================================
  template<real_scalar_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE bool any_(EVE_SUPPORTS(sse2_), logical<wide<T, N, ABI>> const &v) noexcept
  {
    if constexpr( N::value == 1) return v.get(0);
    else                         return eve::detail::any(eve::detail::top_bits{v});
  }

  template<real_scalar_value T, typename N, x86_abi ABI, relative_conditional_expr C>
  EVE_FORCEINLINE bool any_(EVE_SUPPORTS(sse2_), C const &cond,
                            logical<wide<T, N, ABI>> const &v) noexcept
  {
    return eve::detail::any(eve::detail::top_bits{v, cond});
  }

  template<real_scalar_value T, typename N, relative_conditional_expr C>
  EVE_FORCEINLINE bool any_(EVE_SUPPORTS(sse2_), C const &cond,
                            logical<wide<T, N, aggregated_>> const &v) noexcept
  {
    return eve::detail::any(eve::detail::top_bits{v, cond});
  }
}
