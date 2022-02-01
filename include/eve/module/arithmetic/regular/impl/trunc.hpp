//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/raw.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/module/core/constant/maxflint.hpp>
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


  ////////////////////////////////////////////////////////////////////////////////////
  // return integral types

  template<integral_real_value T, typename D>
  EVE_FORCEINLINE constexpr auto trunc_(EVE_SUPPORTS(cpu_), D const &, T xx) noexcept
  requires(is_one_of<D>(types<int_converter, uint_converter>{}))
  {
    if constexpr( has_native_abi_v<T> )
    {
      return D()(xx);
    }
    else
    {
      return apply_over(D()(trunc), xx);
    }
  }
}
