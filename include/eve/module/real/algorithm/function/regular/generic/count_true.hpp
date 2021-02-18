//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/function/to_logical.hpp>

namespace eve::detail
{
  template<value T>
  EVE_FORCEINLINE std::ptrdiff_t count_true_(EVE_SUPPORTS(cpu_), logical<T> const &v) noexcept
  {
    if constexpr(scalar_value<T>)
    {
      return v.value() ? 1 : 0;
    }
    else
    {
      if constexpr(has_aggregated_abi_v<T>)
      {
        auto [sl, sh] = v.slice();
        return eve::count_true(sl) + eve::count_true(sh);
      }
      else
      {
        std::ptrdiff_t r = 0;

        [&]<std::size_t... I>( std::index_sequence<I...> const& )
        {
          r = (r + ... + get<I>(v));
        }( std::make_index_sequence<cardinal_v<T>>{});

        return r;
      }
    }
  }

  template<simd_value T, relative_conditional_expr C>
  EVE_FORCEINLINE std::ptrdiff_t count_true_( EVE_SUPPORTS(cpu_)
                                            , C const &cond
                                            , logical<T> const &v
                                            ) noexcept
  {
    return eve::detail::count_true(eve::detail::top_bits{v,cond});
  }
}
