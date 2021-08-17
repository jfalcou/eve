//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/is_not_nan.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/numeric.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/skeleton_calls.hpp>

namespace eve::detail
{
  ///////////////////////////////////////////////////////////////////////////
  // numeric decorator -> nans are considered equal
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto is_not_equal_(EVE_SUPPORTS(cpu_)
                                , numeric_type const &
                                , T const &a
                                , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(numeric(is_not_equal), a, b);
  }

  template<real_value T, real_value U>
  EVE_FORCEINLINE auto is_not_equal_(EVE_SUPPORTS(cpu_)
                                , numeric_type const &
                                , logical<T> const &a
                                , logical<U> const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(is_not_equal, a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE auto is_not_equal_(EVE_SUPPORTS(cpu_)
                                , numeric_type const &
                                , T const &a
                                , T const &b) noexcept
   {
     auto tmp = is_not_equal(a, b);
     if constexpr(floating_value<T>)  return tmp && (is_not_nan(a) || is_not_nan(b));
     else                             return tmp;
   }

  template<real_value T>
  EVE_FORCEINLINE auto is_not_equal_(EVE_SUPPORTS(cpu_)
                                , numeric_type const &
                                , logical<T> const &a
                                , logical<T> const &b) noexcept
  {
    return is_not_equal(a, b);
  }
}
