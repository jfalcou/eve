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
  EVE_FORCEINLINE bool all_(EVE_SUPPORTS(sse2_), logical<wide<T, N, ABI>> const &v) noexcept
  {
    if constexpr( N::value == 1) return v.get(0);
    else                         return eve::detail::all(eve::detail::top_bits{v});
  }

  template<logical_simd_value T, relative_conditional_expr C>
  EVE_FORCEINLINE bool all_ignore_impl(C const& cond, T const &v) noexcept
  {
    eve::detail::top_bits mmask{v};
    eve::detail::top_bits<T> ignore_mmask{cond};

    mmask |= ~ignore_mmask; // we need 1 in ignored elements;

    return eve::detail::all(mmask);
  }

  template<real_scalar_value T, typename N, x86_abi ABI, relative_conditional_expr C>
  EVE_FORCEINLINE bool all_(EVE_SUPPORTS(sse2_), C const &cond,
                            logical<wide<T, N, ABI>> const &v) noexcept
  {
    return all_ignore_impl(cond, v);
  }

  template<real_scalar_value T, typename N, relative_conditional_expr C>
  EVE_FORCEINLINE bool all_(EVE_SUPPORTS(sse2_), C const &cond,
                            logical<wide<T, N, aggregated_>> const &v) noexcept
  {
    return all_ignore_impl(cond, v);
  }
}
