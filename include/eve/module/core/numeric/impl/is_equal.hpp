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
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/decorator/numeric.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/is_nan.hpp>

namespace eve::detail
{
///////////////////////////////////////////////////////////////////////////
// numeric decorator -> nans are considered equal
template<ordered_value T, ordered_value U>
EVE_FORCEINLINE auto
is_equal_(EVE_SUPPORTS(cpu_),
          numeric_type const&,
          T const& a,
          U const& b) noexcept 
-> common_logical_t<T, U>
{
  return arithmetic_call(numeric(is_equal), a, b);
}

template<ordered_value T, ordered_value U>
EVE_FORCEINLINE auto
is_equal_(EVE_SUPPORTS(cpu_),
          numeric_type const&,
          logical<T> const& a,
          logical<U> const& b) noexcept 
-> common_logical_t<T, U>
{
  return arithmetic_call(is_equal, a, b);
}

template<ordered_value T>
EVE_FORCEINLINE auto
is_equal_(EVE_SUPPORTS(cpu_), numeric_type const&, T const& a, T const& b) noexcept
{
  auto tmp = is_equal(a, b);
  if constexpr( floating_value<T> ) return tmp || (is_nan(a) && is_nan(b));
  else return tmp;
}

template<ordered_value T>
EVE_FORCEINLINE auto
is_equal_(EVE_SUPPORTS(cpu_),
          numeric_type const&,
          logical<T> const& a,
          logical<T> const& b) noexcept
{
  return is_equal(a, b);
}
}
