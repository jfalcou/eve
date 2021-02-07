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
#include <eve/logical.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/top_bits.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/any.hpp>

#include <optional>

namespace eve::detail
{
  template<logical_simd_value T, relative_conditional_expr C>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_SUPPORTS(cpu_), C const &cond, T const &v) noexcept
  {
         if constexpr ( C::is_complete && !C::is_inverted ) return {};
    else if constexpr ( has_emulated_abi_v<T> )
    {
      std::ptrdiff_t first = cond.offset(eve::as_<T>{});
      std::ptrdiff_t last = first + cond.count(eve::as_<T>{});

      while (first != last) {
        if (v.get(first)) return first;
        ++first;
      }

      return {};
    }
    else
    {
      // No ignore, we might luck out even if some elements should not be counted.
      if ( !eve::any(v) ) return {};
      top_bits mmask{v, cond};
      return eve::detail::first_true(mmask);
    }
  }

  template<logical_simd_value T>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  {
    return eve::first_true[ignore_none](v);
  }

}  // namespace eve
