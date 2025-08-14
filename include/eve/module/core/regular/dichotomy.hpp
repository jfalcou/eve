//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/rem.hpp>
#include <iostream>
#include <iomanip>
namespace eve
{
  template<typename Options>
  struct dichotomy_t : callable<dichotomy_t, Options, threshold_option>
  {
    template<typename F, eve::floating_value T0, floating_value T1>
    requires(eve::same_lanes_or_scalar<T0, T1>)
    EVE_FORCEINLINE constexpr common_value_t<T0, T1> operator()(F f, T0 t0, T1 t1) const noexcept
    {
      return EVE_DISPATCH_CALL(f, t0, t1);
    }

    EVE_CALLABLE_OBJECT(dichotomy_t, dichotomy_);
  };


//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var dichotomy
//!   @brief `elementwise_callable` solve f(x) == 0 by dichtomy.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto dichotomy(tauto f, floating_value auto x, floating_value auto y)   noexcept; // 1
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`: [real](@ref eve::floating_value) arguments.
//!     * `f`: callable
//!
//!   **Return value**
//!
//!     1. Returns the solution of f(x) == 0
//!
//!  @groupheader{External references}
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Bisection_method)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/dichotomy.cpp}
//!
//================================================================================================
  inline constexpr auto dichotomy = functor<dichotomy_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename F, typename T, callable_options O> EVE_FORCEINLINE constexpr auto
    dichotomy_(EVE_REQUIRES(cpu_), O const & o, F f, T a, T b) noexcept
    {
      auto tol = [&](){
        if constexpr (O::contains(threshold)) return o[threshold].value(a);
        else  return eve::eps(as(a));
      }();
      if constexpr(floating_simd_value<T>)
      {
        while (true)
        {
          auto  m = eve::average(a, b);
          auto fm = f(m);
          auto test = dist(a, b) <= tol*eve::maxabs(a, b);
          if (eve::all(test)) break;
          auto ltz = is_ltz(f(a)*fm);
          a = if_else(ltz, a, m);
          b = if_else(ltz, m, b);
        }
        return average(a, b);
      }
      else
      {
        int n = 0;
        auto ramp = [&](auto i,  auto ){return (i+1); };
        using w_t =  eve::wide<T>;
        w_t ra{ramp};
        constexpr auto is = T(1)/(cardinal_v<w_t>+T(1));
        tol*= eve::dist(b, a);
        while (true)
        {
          auto fac = (b-a)*is;
          w_t m = fma(fac, ra, a);
          std::cout << std::setprecision(5) << "[a, b] = [" << a << ", " << b << "]\n";
          std::cout << std::setprecision(5) << "m " << m << std::endl;
          auto fm = f(m);
//           std::cout << std::setprecision(5) << "fm " << fm << std::endl;
           std::cout << std::setprecision(5) << "fm*fa " << fm*f(a) << std::endl;
          auto i = first_true( is_ltz(f(a)*fm)).value_or(-1);
           std::cout << " first_true " << i << std::endl;
//           std::cout << i << std::endl;
           b = m.get(i);
           a =  m.get(i-1);
           std::cout << std::scientific << "l2dist(a, b) " << std::log2(dist(a, b)) << std::endl;
//           std::cout << std::scientific << " eve::abs(f(a)) <= tol "<<  (eve::abs(f(a)) <= tol) << std::endl;
           if (dist(a, b) <= tol) break;
          if (++n == 100 ) break;
        }
        std::cout << "n =  " << n << std::endl;
        return eve::average(a, b);
      }
    }
  }
}
