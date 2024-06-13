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
#include <array>

namespace eve::detail
{
  template<typename T, std::ptrdiff_t I0, std::ptrdiff_t I1, callable_options O>
  EVE_FORCEINLINE T byte_swap_pairs_(EVE_REQUIRES(cpu_),
                                     O const &,
                                     T x ,
                                     index_t<I0> const & i0,
                                     index_t<I1> const & i1) noexcept
  {
    if constexpr(simd_value<T>)
    {
      using e_t =  element_type_t<T>;
      constexpr auto S = sizeof(e_t);
      constexpr size_t C = cardinal_v<T>;
      EVE_ASSERT(eve::all(I0 < S && I1 < S), "some index(es) are out or range");
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
      using a_t = std::array<uint8_t, sizeof(T)>;
      a_t a =  bit_cast(x, as<a_t>());
      std::swap(a[I0], a[I1]);
      return bit_cast(a, as<T>());
    }
  }

  // Masked case
  template<conditional_expr C, typename T, std::ptrdiff_t I0, std::ptrdiff_t I1, callable_options O>
  EVE_FORCEINLINE T byte_swap_pairs_(EVE_REQUIRES(cpu_),
                                     C const& cond,
                                     O const &,
                                     T t,
                                     index_t<I0> const & i0,
                                     index_t<I1> const & i1) noexcept
  {
    return mask_op(cond, eve::byte_swap_pairs, t, i0, i1);
  }
}
