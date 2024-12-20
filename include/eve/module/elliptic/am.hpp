//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/traits/common_value.hpp>



namespace eve
{
  template<typename Options>
  struct am_t : elementwise_callable<am_t, Options, threshold_option, modular_option, eccentric_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE
    T operator()(T a) const noexcept { return EVE_DISPATCH_CALL(a); }

    template<eve::floating_value T0, eve::floating_value T1>
    requires (same_lanes_or_scalar<T0, T1>)
    constexpr EVE_FORCEINLINE
    eve::common_value_t<T0, T1> operator()(T0 a, T1 b) const noexcept
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(am_t, am_);
  };

//================================================================================================
//! @addtogroup elliptic
//! @{
//!   @var am
//!   @brief `elementwise_callable` object computing the  Jacobi's Amplitude function.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/elliptic.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto am(floating_value auto u, floating_value auto x)                 noexcept; // 1
//!
//!      //Semantic modifiers
//!      constexpr auto am[modular](floating_value auto u, floating_value auto alpha)    noexcept; // 1
//!      constexpr auto am[eccentric(floating_value auto u, floating_value auto k)       noexcept; // 1
//!      constexpr auto am[threshold = tol](floating_value auto u, floating_value auto x) noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto am[conditional_expr auto c](/*any of the above overloads*/)       noexcept; // 2
//!      constexpr auto am[logical_value autolm](/*any of the above overloads*/)          noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `u`: argument.
//!     * `m`: amplitude parameter (\f$0\le m\le 1).
//!     * `alpha `: modular angle in radian.
//!     * `tol': accuracy tolerance (by defaut [epsilon](@ref eve::epsilon).
//!     * `k`: elliptic modulus (eccentricity) .
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `l`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!      1. return the jacobian amplitude function. Take care that the meaning of the second parameters
//!         depends on the option used (see note below).
//!      2. [The operation is performed conditionally](@ref conditional)
//!
//! @note
//!   * \f$\alpha\f$ is named the modular angle given in radian (modular option).
//!   * \f$ k = \sin\alpha \f$ is named the elliptic modulus or eccentricity (eccentric option).
//!   * \f$ m = k^2 = \sin^2\alpha\f$ is named the parameter (no option).
//!   Each of the above three quantities is completely determined by any of the others (given that they are non-negative).
//!   Thus, they can be used interchangeably (give the right option).

//!  @groupheader{External references}
//!   *  [C++ standard reference: am](https://en.cppreference.com/w/cpp/numeric/special_functions/am)
//!   *  [DLMF: Jacobi Amplitude](https://dlmf.nist.gov/22.16)
//!   *  [Wolfram MathWorld: Jacobi Amplitude](https://mathworld.wolfram.com/JacobiAmplitude.html)
//!   *  [Wikipedia: Jacobi elliptic functions](https://en.wikipedia.org/wiki/Jacobi_elliptic_functions)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/elliptic/am.cpp}
//================================================================================================
  inline constexpr auto am = functor<am_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<floating_value T, callable_options O>
    T am_(EVE_REQUIRES(cpu_), O const& o, T u, T x) noexcept
    {
      auto tol = [&](){
        if constexpr (O::contains(threshold)) return o[threshold].value(x);
        else  return eve::epsilon(x);
      }();
      x =  abs(x);
      if (O::contains(modular)) x = sin(x);
      else if (O::contains(eccentric)) x = sqrt(x);

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
          // the two means converge to a common mean (upto asked threshold)
          // starting with a = 1 and g = k', which were set above.

          auto two_n =  one(as(u));
          int n = 0;
          for (; n < N; n++)
          {
            if (eve::all(eve::is_not_greater_equal(abs(c[n]), tol))) break;
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
  }
}
