//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/concept/value.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/asin.hpp>
#include <eve/function/atan.hpp>
#include <eve/function/average.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_greater_equal.hpp>
#include <eve/function/sin.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/one.hpp>

#include <eve/concept/value.hpp>

#include <eve/detail/overload.hpp>
#include <eve/detail/raberu.hpp>
#include <eve/detail/abi.hpp>

namespace eve
{
  inline constexpr auto tolerance = ::rbr::keyword<struct tolerance_tag>;
  inline constexpr auto mode      = ::rbr::keyword<struct mode_tag>;

  struct angle_   { auto apply(auto x) const { return eve::sin(x);  } };
  struct modulus_ { auto apply(auto x) const { return eve::sqrt(x); } };

  inline constexpr angle_   angle   = {};
  inline constexpr modulus_ modulus = {};
}

namespace eve::detail
{
  template<floating_real_value T> EVE_FORCEINLINE T am_impl(T u, T x, T tol) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto xx = eve::abs(x);
      auto xxisone = xx == one(as(x));
      auto k = if_else(xxisone, T(0.5), xx);
      auto am_kernel = [u, k, tol]()
      {
        constexpr int N = 30; //10 may be sufficent
        std::array<T, N+1> a, g, c;
        a[0] = one(as(u));
        g[0] = sqrt(oneminus(sqr(k)));
        c[0] = k;

        // Perform the sequence of Gaussian transformations of arithmetic and
        // geometric means of successive arithmetic and geometric means until
        // the two means converge to a common mean (upto asked accuracy)
        // starting with a = 1 and g = k', which were set above.

        auto two_n =  one(as(u));
        int n = 0;
        for (; n < N; n++)
        {
          if (eve::all(is_not_greater_equal(abs(c[n]), tol))) break;
          two_n += two_n;
          a[n+1] = average(a[n], g[n]);
          g[n+1] = sqrt(a[n] * g[n]);
          c[n+1] = average(a[n], -g[n]);
        }

        // Prepare for the inverse transformation of phi = x * cm.
        auto phi = two_n * a[n] * u;

        // Perform backward substitution
        for (; n > 0; --n)
        {
          phi = average(phi, asin(c[n]*sin(phi)/a[n]) );
        }
        return phi;
      };

      T r;
      if (eve::any(xxisone)) r = fms(T(2), atan(exp(u)), pio_2(as(xx)));
      if (eve::all(xxisone)) return r;
      return if_else(xxisone, r, am_kernel());
    }
    else
    {
      return apply_over(am, u, x, tol);
    }
  }

  struct am_nope  { auto apply(auto x) const { return x;  } };

  template< floating_real_value U, floating_real_value X
          , typename... Settings
          >
  EVE_FORCEINLINE U am_(EVE_SUPPORTS(cpu_), U u, X x, Settings... s) noexcept
  requires( sizeof...(Settings) <= 2)
  {
    auto const option = rbr::settings{s...};

    return arithmetic_call( [](auto a,auto b,auto t) { return am_impl(a,b,t); }
                          , u
                          , option[mode | am_nope{}].apply(x)
                          , option[tolerance | eps(as<element_type_t<U>>())]
                          );
  }
}
