//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/copysign.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_unordered.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/signnz.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <eve/module/real/math/detail/generic/atan_kernel.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<floating_value T, floating_value U>
  EVE_FORCEINLINE  auto atan2_(EVE_SUPPORTS(cpu_)
                            , pedantic_type const &
                            , T const &a
                            , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(pedantic(atan2), a, b);
  }

  template<floating_value T>
  EVE_FORCEINLINE auto atan2_( EVE_SUPPORTS(cpu_)
                             , pedantic_type const &
                             , T const &a0
                             , T const &a1
                             ) noexcept
  requires  has_native_abi_v<T>
  {
    if constexpr(scalar_value<T> && platform::supports_nans)
    {
      if (is_unordered(a0, a1)) return nan(eve::as(a0));
    }
    T a00 = a0, a10 = a1;
    auto test1 =  eve::is_infinite(a0)&& eve::is_infinite(a1);
    if constexpr(platform::supports_infinites)
    {
      a00 =  eve::if_else(test1, eve::copysign(one(eve::as(a0)), a00), a00);
      a10 =  eve::if_else(test1, eve::copysign(one(eve::as(a0)), a10), a10);
    }

    T q = eve::abs(a00/a10);
    T z = atan_kernel(q, rec(q));
    T sgn = signnz(a0);
    if constexpr(scalar_value<T>)
    {
      z = (is_positive(a10)? z: pi(eve::as<T>())-z)*sgn;
      return is_eqz(a00) ? if_else(is_negative(a10), pi(eve::as(a00))*sgn, eve::zero) : z;
    }
    else
    {
      z = eve::if_else(eve::is_positive(a10), z, eve::pi(eve::as(a0))-z)*sgn;
      z = eve::if_else( eve::is_eqz(a00),
                        eve::if_else( eve::is_negative(a10),  eve::pi(eve::as(a0))*sgn, eve::zero),
                        z);
      if constexpr(platform::supports_nans) return  eve::if_else( is_unordered(a00, a10), eve::allbits, z);
      else                                  return z;
    }
  }
}
