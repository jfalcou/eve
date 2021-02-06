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
#include <eve/detail/implementation.hpp>
#include <eve/function/any.hpp>

#include <optional>

namespace eve::detail
{
  template<logical_simd_value T, relative_conditional_expr C>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_SUPPORTS(cpu_), C const &cond, T const &v) noexcept
  {
         if constexpr ( C::is_complete && !C::is_inverted ) return {};
    else if constexpr ( has_aggregated_abi_v<T> && C::is_complete)
    {
      if (!eve::any(v)) return {};

      auto [l, h] = v.slice();

      std::ptrdiff_t res;

      if (auto h_res = eve::first_true(h)) res = *h_res + T::static_size / 2;
      if (auto l_res = eve::first_true(l)) res = *l_res;

      return res;
    }
    else if constexpr ( has_aggregated_abi_v<T> )
    {
      // Issue #535: improve
      return eve::first_true(cond.mask(eve::as_<T>{}) && v);
    }
    else
    {
      std::ptrdiff_t first = cond.offset(eve::as_<T>{});
      std::ptrdiff_t last = first + cond.count(eve::as_<T>{});
      while (first != last) {
        if (v.get(first)) return first;
        ++first;
      }
      return {};
    }
  }

  template<logical_simd_value T>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  {
    return eve::first_true[ignore_none](v);
  }

}  // namespace eve
