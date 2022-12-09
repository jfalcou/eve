//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/common_value.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/decorator/numeric.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/bit_or.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/is_unordered.hpp>
#include <eve/module/core/regular/logical_and.hpp>

namespace eve::detail
{
template<typename T, typename U>
EVE_FORCEINLINE auto
min_(EVE_SUPPORTS(cpu_),
     numeric_type const&,
     T const& v0,
     U const& v1) noexcept
-> decltype(min(v0, v1))
{
  return arithmetic_call(numeric(min), v0, v1);
}

template<ordered_value T>
EVE_FORCEINLINE auto
min_(EVE_SUPPORTS(cpu_), numeric_type const&, T const& v0, T const& v1) noexcept
{
  if constexpr( integral_value<T> ) return eve::min(v0, v1);
  else
  {
    if constexpr( eve::platform::supports_invalids )
    {
      if constexpr( scalar_value<T> )
      {
        if( is_nan(v0) ) return v1;
        else if( is_nan(v1) ) return v0;
        else if( is_eqz(v0) && is_eqz(v1) ) return bit_or(v0, v1);
        else return min(v0, v1);
      }
      else
      {
        auto tmp = if_else(is_nan(v0), v1, if_else(is_nan(v1), v0, min(v0, v1)));
        return if_else(is_eqz(v0) && is_eqz(v1), bit_or(v0, v1), tmp);
      }
    }
    else
    {
      if constexpr( scalar_value<T> )
      {
        return (is_eqz(v0) && is_eqz(v1) ? bit_or(v0, v1) : eve::min(v0, v1));
      }
      else { return if_else(is_eqz(v0) && is_eqz(v1), bit_or(v0, v1), eve::min(v0, v1)); }
    }
  }
}

//================================================================================================
// N parameters
//================================================================================================
template<ordered_value T0, ordered_value T1, ordered_value... Ts>
auto
min_(EVE_SUPPORTS(cpu_), numeric_type const&, T0 a0, T1 a1, Ts... args) noexcept
  -> common_value_t<T0, T1, Ts...>
{
  auto m    = numeric(min);
  using r_t = common_value_t<T0, T1, Ts...>;
  r_t that(m(r_t(a0), r_t(a1)));
  ((that = m(that, r_t(args))), ...);
  return that;
}
}
