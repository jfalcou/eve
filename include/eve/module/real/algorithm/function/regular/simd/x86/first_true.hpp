//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2021 Joel FALCOU
  Copyright 2021 Jean-Thierry LAPRESTE
  Copyright 2021 Denis YAROSHEVSKIY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
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
      top_bits mmask{v, cond};
      return eve::detail::first_true(mmask);
    }
  }
}
