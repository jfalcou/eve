//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_MATH_FUNCTION_GENERIC_SINPICOSPI_HPP_INCLUDED
#define EVE_MODULE_MATH_FUNCTION_GENERIC_SINPICOSPI_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/module/math/detail/generic/rem2.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>

#include <type_traits>
#include <utility>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto
  sinpicospi_(EVE_SUPPORTS(cpu_), restricted_type const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return restricted_(sincos)(a0 * Pi<T>());
    }
    else
      return apply_over2(restricted_(sinpicospi), a0);
  }

  //////////////////////////////////////////////////////////////////////////////
  /// big medium small
  template<decorator D, floating_real_value T>
  EVE_FORCEINLINE constexpr auto sinpicospi_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( scalar_value<T> )
      {
        if( is_not_finite(a0) )
          return std::make_tuple(Nan<T>(), Nan<T>());
      }
      T x = abs(a0);
      if constexpr( scalar_value<T> )
      {
        if( x > Maxflint<T>() )
          return std::make_tuple(T {0}, T(1));
      }
      else
      {
        auto invalid = is_not_finite(x);
        x = if_else(x > Maxflint(as(x)), eve::zero_, x);
        x = if_else(invalid, eve::allbits_, x);
      }
      auto [fn, xr, dxr] = rem2(x);
      return sincos_finalize(bitofsign(a0), fn, xr, dxr);
    }
    else
      return apply_over2(D()(sinpicospi), a0);
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto sinpicospi_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto x = abs(a0);
      if( all(x <= T(0.25)) )
        return restricted_(sinpicospi)(a0);
      else
        return big_(sinpicospi)(a0);
    }
    else
      return apply_over2(sinpicospi, a0);
  }
}

#endif
