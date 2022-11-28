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
#include <eve/module/core/constant/eps.hpp>
#include <eve/module/core/decorator/fuzzy.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/convert.hpp>
#include <eve/module/core/regular/is_greater_equal.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/saturated/prev.hpp>
#include <eve/module/core/saturated/sub.hpp>

namespace eve::detail
{
template<floating_real_value T, floating_real_value U>
EVE_FORCEINLINE auto
is_greater_equal_(EVE_SUPPORTS(cpu_),
                  almost_type const&,
                  T const& a,
                  U const& b) noexcept
-> common_logical_t<T, U>
{
  return arithmetic_call(almost(is_greater_equal), a, b, 3 * eps(as(a)));
}

template<floating_real_value T, floating_real_value U>
EVE_FORCEINLINE auto
is_greater_equal_(EVE_SUPPORTS(cpu_),
                  almost_type const&,
                  logical<T> const& a,
                  logical<U> const& b) noexcept
-> common_logical_t<T, U>
{
  return arithmetic_call(is_greater_equal, a, b);
}

template<floating_real_value T, floating_real_value U, real_value V>
EVE_FORCEINLINE auto
is_greater_equal_(EVE_SUPPORTS(cpu_),
                  almost_type const&,
                  T const& a,
                  U const& b,
                  V const& tol) noexcept
-> common_logical_t<T, U>
{
  if constexpr( integral_value<V> )
  {
    using c_t = std::conditional_t<scalar_value<T>, U, T>;
    c_t aa(a);
    c_t bb(b);
    return almost(is_greater_equal)(aa, bb, tol);
  }
  else return arithmetic_call(almost(is_greater_equal), a, b, tol);
}

template<floating_real_value T, value V>
EVE_FORCEINLINE auto
is_greater_equal_(EVE_SUPPORTS(cpu_),
                  almost_type const&,
                  T const                 & a,
                  T const                 & b,
                  [[maybe_unused]] V const& tol) noexcept
{
  if constexpr( integral_value<V> )
  {
    if constexpr( simd_value<V> && scalar_value<T> )
    {
      using c_t = as_wide_t<T, cardinal_t<V>>;
      using i_t = as_integer_t<T, unsigned>;
      return almost(is_greater_equal)(c_t(a), c_t(b), convert(tol, as<i_t>()));
    }
    else { return is_greater_equal(a, saturated(prev)(b, tol)); }
  }
  else { return is_greater_equal(a, saturated(sub)(b, tol * max(eve::abs(a), eve::abs(b)))); }
}
}
