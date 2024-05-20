//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/module/core/constant/exponentmask.hpp>
#include <eve/module/core/constant/half.hpp>
#include <eve/module/core/constant/maxexponentm1.hpp>
#include <eve/module/core/constant/maxexponentp1.hpp>
#include <eve/module/core/constant/nbmantissabits.hpp>
#include <eve/module/core/constant/twotonmb.hpp>
#include <eve/module/core/regular/add.hpp>
#include <eve/module/core/regular/bit_and.hpp>
#include <eve/module/core/regular/bit_andnot.hpp>
#include <eve/module/core/regular/bit_notand.hpp>
#include <eve/module/core/regular/bit_or.hpp>
#include <eve/module/core/regular/bit_shr.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_denormal.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_greater.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/module/core/regular/is_not_finite.hpp>
#include <eve/module/core/regular/logical_notand.hpp>
#include <eve/module/core/regular/shr.hpp>

namespace eve::detail
{
template<typename T>
EVE_FORCEINLINE constexpr auto pedantic_frexp(T a0) noexcept
{
  using i_t = as_integer_t<T, signed>;
  if constexpr( simd_value<T> )
  {
    using elt_t = element_type_t<T>;
    i_t t(0);
    if constexpr( eve::platform::supports_denormals )
    {
      auto test = is_denormal(a0);
      t         = if_else(test, nbmantissabits(eve::as<T>()), eve::zero);
      a0        = if_else(test, twotonmb(eve::as<T>()) * a0, a0);
    }


    auto emask = exponentmask(as<T>());
    auto e     = bit_cast(bit_and(a0,emask),as(emask)); // extract exp.
    auto x     = bit_notand(emask, a0);
    e          = bit_shr(e, nbmantissabits(eve::as<elt_t>())) - maxexponentm1(eve::as<elt_t>());
    auto r0    = bit_or(half(eve::as<T>()), x);
    auto test0 = is_nez(a0);
    auto test1 = is_greater(e, maxexponentp1(eve::as<T>()));
    auto ee    = if_else(logical_andnot(test0, test1), e, eve::zero);

    if constexpr( eve::platform::supports_denormals ) { ee -= t; }
    return eve::zip(if_else(test0, add[test1](r0, a0), eve::zero), ee);
  }
  else if constexpr( scalar_value<T> )
  {
    if( a0 == 0 || is_not_finite(a0) ) { return eve::zip(a0, i_t(0)); }
    else if constexpr( scalar_value<T> )
    {
      auto const nmb = nbmantissabits(eve::as<T>());
      i_t        e   = bit_and(exponentmask(as<T>()), a0); // extract exp.
      if constexpr( eve::platform::supports_denormals )
      {
        i_t t = i_t(0);
        if( is_eqz(e) ) // denormal
        {
          a0 *= twotonmb(eve::as<T>());
          e = bit_and(exponentmask(as<T>()), a0); // extract exp. again
          t = nmb;
        }
        T x = bit_andnot(a0, exponentmask(as<T>()));         // clear exp. in a0
        e   = bit_shr(e, nmb) - maxexponentm1(eve::as<T>()); // compute exp.
        if( e > maxexponentp1(eve::as<T>()) ) return eve::zip(a0, i_t(0));
        e -= t;
        return eve::zip(bit_or(x, half(eve::as<T>())), e);
      }
      else
      {
        T x = bit_andnot(a0, exponentmask(as<T>()));         // clear exp. in a0
        e   = bit_shr(e, nmb) - maxexponentm1(eve::as<T>()); // compute exp.
        if( e > maxexponentp1(eve::as<T>()) ) return eve::zip(a0, i_t(0));
        return eve::zip(bit_or(x, half(eve::as<T>())), e);
      }
    }
  }
}

  template<floating_value T, callable_options O>
  EVE_FORCEINLINE constexpr auto ifrexp_(EVE_REQUIRES(cpu_), O const&, T a0) noexcept
  {
    if constexpr(O::contains(pedantic2))
    {
      return pedantic_frexp(a0);
    }
    else
    {
      using elt_t = element_type_t<T>;
      auto emask  = exponentmask(as<T>());
      auto r1     = bit_cast(bit_and(a0,emask), as(emask));
      auto x      = bit_notand(emask, a0);
      auto res    = eve::zip( bit_or(half(eve::as<T>()), x)
                            , bit_shr(r1, nbmantissabits(eve::as<elt_t>())) - maxexponentm1(eve::as<elt_t>())
                            );

      if constexpr(O::contains(raw2)) return res;
      else
      {
        auto a0eqz  = is_eqz(a0);

        if constexpr( scalar_value<T> )
        {
          using i_t = as_integer_t<T>;
          if( a0eqz ) return eve::zip(T(0), i_t(0));
        }
        return eve::zip(if_else(a0eqz, eve::zero, get<0>(res)), if_else(a0eqz, eve::zero, get<1>(res)));
      }
    }
  }

}
