//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/constant/eps.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/dist.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/function/fuzzy.hpp>
#include <eve/function/nb_values.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto is_equal_(EVE_SUPPORTS(cpu_)
                                , almost_type const &
                                , T const &a
                                , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(almost(is_equal), a, b, 3*eps(as(a)));
  }

  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto is_equal_(EVE_SUPPORTS(cpu_)
                                , almost_type const &
                                , logical<T> const &a
                                , logical<U> const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(is_equal, a, b);
  }

  template<floating_real_value T, floating_real_value U, real_value V>
  EVE_FORCEINLINE auto is_equal_(EVE_SUPPORTS(cpu_)
                                , almost_type const &
                                , T const &a
                                , U const &b
                               ,  V const &tol) noexcept
  requires compatible_values<T, U>
  {
    if constexpr(integral_value<V>)
    {
      using c_t = std::conditional_t<scalar_value<T>, U, T>;
      c_t aa(a);
      c_t bb(b);
      return almost(is_equal)(aa, bb, tol);
    }
    else return arithmetic_call(almost(is_equal), a, b, tol);
  }

  template<floating_real_value T, value V>
  EVE_FORCEINLINE auto is_equal_(EVE_SUPPORTS(cpu_)
                                , almost_type const &
                                , T const &a
                                , T const &b
                                , [[maybe_unused]] V const &tol) noexcept
  {
    if constexpr(integral_value<V>)
    {
      if constexpr(simd_value<V> && scalar_value<T>)
      {
        using c_t = as_wide_t<T, cardinal_t<V>>;
        using i_t = as_integer_t<T, unsigned>;
        return almost(is_equal)(c_t(a), c_t(b), convert(tol, as<i_t>()));
      }
      else
      {
        return convert(nb_values(a, b) <= tol, as(logical<element_type_t<T>>()));
      }
    }
    else
    {
      return is_less_equal(dist(a, b), tol*max(eve::abs(a), eve::abs(b)));
    }
  }
}
