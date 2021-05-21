//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/module/real/math/detail/generic/rem2.hpp>
#include <eve/module/real/math/detail/generic/trig_finalize.hpp>

#include <type_traits>
#include <tuple>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr std::tuple<T, T>
  sinpicospi_(EVE_SUPPORTS(cpu_), restricted_type const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return restricted(sincos)(a0 * pi(eve::as<T>()));
    }
    else
      return apply_over2(restricted(sinpicospi), a0);
  }

  //////////////////////////////////////////////////////////////////////////////
  /// big medium small
  template<decorator D, floating_real_value T>
  EVE_FORCEINLINE constexpr std::tuple<T, T>
  sinpicospi_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( scalar_value<T> )
      {
        if( is_not_finite(a0) )
          return {nan(eve::as<T>()), nan(eve::as<T>())};
      }
      T x = abs(a0);
      if constexpr( scalar_value<T> )
      {
        if( x > maxflint(eve::as<T>()) )
          return {T{0}, T(1)};
      }
      else
      {
        auto invalid = is_not_finite(x);
        x = if_else(x > maxflint(eve::as(x)), eve::zero, x);
        x = if_else(invalid, eve::allbits, x);
      }
      auto [fn, xr, dxr] = rem2(x);
      auto [s, c] = sincos_finalize(bitofsign(a0), fn, xr, dxr);
      return {s, c};
    }
    else
      return apply_over2(D()(sinpicospi), a0);
  }

  template<typename T>
  EVE_FORCEINLINE constexpr std::tuple<T, T>
  sinpicospi_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto x = abs(a0);
      if( eve::all(x <= T(0.25)) )
        return restricted(sinpicospi)(a0);
      else
        return big(sinpicospi)(a0);
    }
    else
      return apply_over2(sinpicospi, a0);
  }
}
