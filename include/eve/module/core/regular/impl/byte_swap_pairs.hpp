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
#include <eve/module/core/regular/shuffle.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <bit>
#include <array>

namespace eve::detail
{
  template<typename T, std::ptrdiff_t I0, std::ptrdiff_t I1, callable_options O>
  EVE_FORCEINLINE T byte_swap_pairs_(EVE_REQUIRES(cpu_), O const &, T x, index_t<I0>, index_t<I1>) noexcept
  {
    if constexpr(simd_value<T>)
    {
      using e_t =  element_type_t<T>;
      constexpr auto S = sizeof(e_t);
      constexpr size_t C = cardinal_v<T>;
      using u8_t = wide<std::uint8_t, fixed<S*C>>;
      auto p = [](auto i,  auto){
        auto ii = i%S;
        auto jj = (i/S)*S;
        return (ii == I0) ? I1+jj :(ii == I1 ? I0+jj : i) ;
      };
      auto x8 = bit_cast(x, as<u8_t>());
      auto y = eve::shuffle(x8, eve::as_pattern(p));
      x = bit_cast(y, as<T>());
      return x;
    }
    else if constexpr(scalar_value<T>)
    {
      using a_t = std::array<std::uint8_t, sizeof(T)>;
      a_t a =  bit_cast(x, as<a_t>());
      std::swap(a[I0], a[I1]);
      return bit_cast(a, as<T>());
    }
  }
}
