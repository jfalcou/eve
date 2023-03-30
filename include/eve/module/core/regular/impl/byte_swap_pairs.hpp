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
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/bit_xor.hpp>
#include <eve/module/core/regular/bit_shl.hpp>
#include <eve/module/core/regular/bit_shr.hpp>
#include <bit>

namespace eve::detail
{
  template<unsigned_value T, auto I0, auto I1>
  EVE_FORCEINLINE T
  byte_swap_pairs_(EVE_SUPPORTS(cpu_), T x
                  , std::integral_constant<size_t, I0> const & i0
                  , std::integral_constant<size_t, I1> const & i1) noexcept;

  template<unsigned_value T, auto I0, auto I1>
  EVE_FORCEINLINE T
  byte_swap_pairs_(EVE_SUPPORTS(cpu_), T x
                  , std::integral_constant<size_t, I0> const & i0
                  , std::integral_constant<size_t, I1> const & i1) noexcept
  {

    if constexpr(simd_value<T>)
    {
      using e_t =  element_type_t<T>;
      constexpr auto S = sizeof(e_t);
      constexpr size_t C = cardinal_v<T>;
      EVE_ASSERT(I0 < S && I1 < S, "some index(es) are out or range");
      using u8_t = wide<uint8_t, fixed<S*C>>;
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
      using w_t = wide<T>;
      auto wx = w_t(x);
      using u_t = wide<uint8_t, fixed<sizeof(T)>>;
      return byte_swap_pairs(wx, i0, i1).get(0);
    }
  }

  // Masked case
  template<conditional_expr C, unsigned_value T, auto I0, auto I1>
  EVE_FORCEINLINE auto
  byte_swap_pairs_(EVE_SUPPORTS(cpu_), C const& cond, T const& t
                  , std::integral_constant<size_t, I0> const & i0
                  , std::integral_constant<size_t, I1> const & i1) noexcept
  {
    return mask_op(cond, eve::byte_swap_pairs, t, i0, i1);
  }
}
