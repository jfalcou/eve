//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/decorator/pedantic.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/bit_and.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/is_unordered.hpp>
#include <eve/module/core/regular/logical_and.hpp>
#include <eve/arch/platform.hpp>

namespace eve::detail
{
template<ordered_value T, ordered_value U>
EVE_FORCEINLINE auto
max_(EVE_SUPPORTS(cpu_),
     pedantic_type const&,
     T const& v0,
     U const& v1) noexcept
-> decltype(max(v0, v1))
{
  return arithmetic_call(pedantic(max), v0, v1);
}

template<ordered_value T>
EVE_FORCEINLINE auto
max_(EVE_SUPPORTS(cpu_), pedantic_type const&, T const& v0, T const& v1) noexcept
{
  if constexpr( integral_value<T> ) return eve::max(v0, v1);
  else
  {
    if constexpr( eve::platform::supports_invalids )
    {
      if constexpr( scalar_value<T> )
      {
        if( is_eqz(v0) && is_eqz(v1) ) return bit_and(v0, v1);
        return is_unordered(v0, v1) ? v0 : eve::max(v0, v1);
      }
      else
      {
        auto tmp = if_else(is_unordered(v0, v1), v0, eve::max(v0, v1));
        return if_else(is_eqz(v0) && is_eqz(v1), bit_and(v0, v1), tmp);
      }
    }
    else
    {
      if constexpr( scalar_value<T> )
      {
        return (is_eqz(v0) && is_eqz(v1) ? bit_and(v0, v1) : eve::max(v0, v1));
      }
      else { return if_else(is_eqz(v0) && is_eqz(v1), bit_and(v0, v1), eve::max(v0, v1)); }
    }
  }
}

//================================================================================================
// N parameters
//================================================================================================
template<ordered_value T0, ordered_value T1, ordered_value... Ts>
auto
max_(EVE_SUPPORTS(cpu_), pedantic_type const&, T0 a0, T1 a1, Ts... args) noexcept
-> decltype(max(a0, a1, args...))
{
  auto m    = pedantic(max);
  using r_t = decltype(max(a0, a1, args...));
  r_t that(m(r_t(a0), r_t(a1)));
  ((that = m(that, r_t(args))), ...);
  return that;
}
}
