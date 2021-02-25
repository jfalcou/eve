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
  template<real_scalar_value T, typename N, x86_abi ABI, relative_conditional_expr C>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_SUPPORTS(sse2_), C const &cond, logical<wide<T, N, ABI>> const &v) noexcept
  {
    if constexpr ( C::is_complete && !C::is_inverted ) return {};
    else
    {
      // We override here because there top_bits is already the optimial test
      // and there is no reason to do any before hand.
      top_bits mmask{v, cond};
      return eve::detail::first_true(mmask);
    }
  }
}
