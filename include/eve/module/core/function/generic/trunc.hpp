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

#include <eve/detail/implementation.hpp>
#include <eve/constant/eps.hpp>
#include <eve/function/raw.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/minus.hpp>
#include <eve/function/tolerant.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr auto trunc_(EVE_SUPPORTS(cpu_)
                                       , T const &a0) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
           if constexpr(integral_value<T>) return a0;
      else if constexpr(floating_value<T>)
      {
        auto already_integral = is_not_less_equal(eve::abs(a0), maxflint(eve::as<T>()));
             if constexpr(scalar_value<T>) return already_integral ? a0 :raw(trunc)(a0);
        else if constexpr(simd_value<T>)   return if_else(already_integral, a0, eve::raw(trunc)(a0));
      }
    }
    else return apply_over(trunc, a0);
  }

  // -----------------------------------------------------------------------------------------------
  // Raw case
  template<real_value T>
  EVE_FORCEINLINE constexpr auto trunc_(EVE_SUPPORTS(cpu_)
                                       , raw_type const &
                                       , T const &a0) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      using elt_t = element_type_t<T>;
      using i_t = as_integer_t<elt_t>;
      if constexpr(integral_value<T>)      return a0;
      else if constexpr(floating_value<T>) return convert(convert(a0, as<i_t>()), as<elt_t>());
    }
    else return apply_over(trunc, a0);
  }

  // -----------------------------------------------------------------------------------------------
  // tolerant case
  template<floating_real_value T, value U>
  EVE_FORCEINLINE constexpr auto trunc_(EVE_SUPPORTS(cpu_)
                                       , tolerant_type const &
                                       , T const &a0
                                       , U const &tol) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      return minus[is_ltz(a0)](tolerant(floor)(eve::abs(a0), tol));
    }
    else return apply_over(tolerant(trunc), a0, tol);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto trunc_(EVE_SUPPORTS(cpu_)
                                       , tolerant_type const &
                                       , T const &a0) noexcept
  {
    return tolerant(trunc), a0, 3*eps(as(a0));
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto trunc_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op( EVE_CURRENT_API{}, cond, eve::trunc, t);
  }

  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto trunc_(EVE_SUPPORTS(cpu_), C const &cond, tolerant_type const &, U const &t) noexcept
  {
    return mask_op( EVE_CURRENT_API{}, cond, tolerant(eve::trunc), t);
  }

  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto trunc_(EVE_SUPPORTS(cpu_), C const &cond, raw_type const &, U const &t) noexcept
  {
    return mask_op( EVE_CURRENT_API{}, cond, raw(eve::trunc), t);
  }

}
