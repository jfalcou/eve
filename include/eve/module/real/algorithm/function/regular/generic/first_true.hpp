//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
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
      std::ptrdiff_t first = cond.offset(eve::as<T>{});
      std::ptrdiff_t last = first + cond.count(eve::as<T>{});

      while (first != last) {
        if (v.get(first)) return first;
        ++first;
      }

      return {};
    }
    // This is pretty good for aggreagted as well.
    else if constexpr ( !top_bits<T>::is_cheap )
    {
      // No ignore, we might luck out even if some elements should not be counted.
      if ( !eve::any(v) ) return {};

      top_bits mmask{v, cond};
      if constexpr ( C::is_complete ) return *detail::first_true(mmask); // optimizes a check on clang
      else                            return detail::first_true(mmask);
    }
    else
    {
      top_bits mmask{v, cond};
      return detail::first_true(mmask);
    }
  }

  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_SUPPORTS(cpu_), bool v) noexcept
  {
    if (!v) return std::nullopt;
    return 0;
  }

  template<value T>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  {
    if constexpr ( !scalar_value<T> ) return eve::first_true[ignore_none](v);
    else
    {
      if (!v) return std::nullopt;
      return 0;
    }
  }

}  // namespace eve
