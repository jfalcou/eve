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
#include <eve/detail/abi.hpp>

namespace eve
{
  //================================================================================================
  // Function decorators mark-up used in function overloads
  struct ell_angle_type : decorator_
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return  [f](auto&&... args)
      {
        return f(ell_angle_type{}, std::forward<decltype(args)>(args)...);
      };
    }
  };

  //================================================================================================
  // Function decorator - ell_angle mode
  inline constexpr ell_angle_type const ell_angle = {};

  //================================================================================================
  // Function decorators mark-up used in function overloads
  struct ell_modulus_type : decorator_
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return  [f](auto&&... args)
      {
        return f(ell_modulus_type{}, std::forward<decltype(args)>(args)...);
      };
    }
  };

  //================================================================================================
  // Function decorator - modulus mode
  inline constexpr ell_modulus_type const ell_modulus = {};

}


namespace eve::detail
{
  template<floating_real_value T, floating_real_value U,  floating_real_value V>
  EVE_FORCEINLINE T am_(EVE_SUPPORTS(cpu_)
                       , T u
                       , T x
                       , T tol = eps(as<T>())) noexcept
  {
    return arithmetic_call(am, u, x, tol);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T am_(EVE_SUPPORTS(cpu_)
                       , T u
                       , T x
                       , T tol = eps(as<T>())) noexcept
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
//          if (eve::all(is_not_greater_equal(eve::abs(a[n] - g[n]),tol*a[n]))) break;
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
      return apply_over(am, u, x, tol);
    }

  template<floating_real_value T, floating_real_value U /*, *floating_real_value V*/,  decorator D>
  EVE_FORCEINLINE T am_(EVE_SUPPORTS(cpu_)
                       , D const &
                       , T u
                       , U x
                       ) noexcept
  {
    return D()(am)(u, x, eps(as<element_type_t<T>>()));
  }

  template<floating_real_value T, floating_real_value U, floating_real_value V,  decorator D>
  EVE_FORCEINLINE T am_(EVE_SUPPORTS(cpu_)
                       , D const &
                       , T u
                       , U x
                       , V tol
                       ) noexcept
  {
    x = eve::abs(x);
    if constexpr(std::is_same_v<D, regular_type>)
    {
      return am(u,x,tol);
    }
    else if constexpr(std::is_same_v<D, ell_modulus_type>)
    {
      return am(u,sqrt(x),tol);
    }
    else if constexpr(std::is_same_v<D, ell_angle_type>)
    {
      return am(u,sin(x),tol);
    }
  }

}
