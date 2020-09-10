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
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/binarize.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/saturated.hpp>

#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Decorated
  template<real_value T, decorator D>
  EVE_FORCEINLINE constexpr T oneminus_(EVE_SUPPORTS(cpu_), D const &, T const &v) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      using elt_t = element_type_t<T>;
      if constexpr( std::is_same_v<D, regular_type> || std::is_floating_point_v<elt_t> )
      {
        return one(eve::as<T>()) - v;
      }
      else if constexpr( std::is_same_v<D, saturated_type> )
      {
        if constexpr( std::is_unsigned_v<elt_t> )
        {
          return binarize(is_eqz(v));
        }
        if constexpr( scalar_value<T> )
        {
          return (v <= Valmin(eve::as(v)) + 2) ? Valmax(eve::as(v)) : oneminus(v);
        }
        else if constexpr( simd_value<T> )
        {
          return if_else(v < Valmin(eve::as(v)) + 2, Valmax(eve::as(v)), oneminus(v));
        }
      }
    }
    else
    {
      return apply_over(D()(oneminus), v);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // regular
  template<real_value T>
  EVE_FORCEINLINE constexpr T oneminus_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  {
    return oneminus(regular_type(), v);
  }


  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto oneminus_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op( EVE_CURRENT_API{}, cond, eve::oneminus, t);
  }

  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto oneminus_(EVE_SUPPORTS(cpu_), C const &cond, saturated_type const &, U const &t) noexcept
  {
    return mask_op( EVE_CURRENT_API{}, cond, saturated_(eve::oneminus), t);
  }
}
