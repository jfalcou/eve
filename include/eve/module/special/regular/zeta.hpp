/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/detail/hz_device.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

namespace eve
{
  template<typename Options>
  struct zeta_t : elementwise_callable<zeta_t, Options>
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(T v) const noexcept
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(zeta_t, zeta_);
  };

  //================================================================================================
  //! @addtogroup special
  //! @{
  //!   @var zeta
  //!   @brief Computes the Riemann \f$\zeta\f$ function.
  //!
  //!   @groupheader{Header file}
  //!
  //!   @code
  //!   #include <eve/module/special.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      // Regular overload
  //!      constexpr auto zeta(floating_value auto x)                          noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto zeta[conditional_expr auto c](floating_value auto x) noexcept; // 2
  //!      constexpr auto zeta[logical_value auto m](floating_value auto x)    noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`: [floating value](@ref floating_value).
  //!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //!   **Return value**
  //!
  //!     1. The value of the Riemann function defined as
  //!        \f$\displaystyle \zeta(s)=\sum_{n=0}^\infty \frac1{n^s}\f$ for \f$s > 1\f$
  //!        and using analytic continuation elsewhere, is returned.
  //!     2. [The operation is performed conditionnaly](@ref conditional).
  //!
  //!  @groupheader{External references}
  //!   *  [Wikipedia: Riemann zeta function](https://en.wikipedia.org/wiki/Riemann_zeta_function)
  //!   *  [Wolfram MathWorld: Riemann Zeta Function](https://mathworld.wolfram.com/RiemannZetaFunction.html)
  //!
  //!   @groupheader{Example}
  //!   @godbolt{doc/special/zeta.cpp}
  //================================================================================================
  inline constexpr auto zeta = functor<zeta_t>;
  //================================================================================================
  //! @}
  //================================================================================================

  namespace detail
  {

    template<callable_options O, typename T>
    constexpr T zeta_(EVE_REQUIRES(cpu_), O const&, T x) noexcept
    {
      using elt_t = element_type_t<T>;
      //
      // This is algorithm 3 from:
      //
      // "An Efficient Algorithm for the Riemann Zeta Function", P. Borwein,
      // Canadian Mathematical Society, Conference Proceedings.
      // See: http://www.cecm.sfu.ca/personal/pborwein/PAPERS/P155.pdf
      //
      auto zetp = [](auto s){
        auto      sc = oneminus(s);
        const int n  = if_else(sizeof(elt_t) == 8, 18, 7);
        auto      ss(zero(as{s}));
        auto      two_n = ldexp(T(1), n);
        auto      ej_sign(one(as{s}));
        for( int j = 1; j <= n; ++j )
        {
          ss += ej_sign * -two_n * pow_abs(T(j), -s);
          ej_sign = -ej_sign;
        }
        auto ej_ss(one(as{s}));
        auto ej_term(one(as{s}));
        for( int j = n; j <= 2 * n - 1; ++j )
        {
          ss += ej_sign * (ej_ss - two_n) * pow_abs(T(inc(j)), -s);
          ej_sign = -ej_sign;
          ej_term *= 2 * n - j;
          ej_term /= j - n + 1;
          ej_ss += ej_term;
        }
        auto z = -ss / (two_n * (-powm1(T(2), sc)));
        return if_else(s == one(as{s}), allbits, z);
      };
      auto r       = nan(as{x});
      auto notdone = x != one(as{x}) || is_not_nan(x);
      if( eve::any(notdone) )
      {
        notdone = next_interval(zetp, notdone, is_gez(x), r, x);
        if( eve::any(notdone) )
        {
          auto reflec = [zetp](auto xx){
            auto vp1 = oneminus(xx); // 1-x
            return 2 * pow_abs(2 * pi(as{xx}), -vp1) * cospi(T(0.5) * vp1) * tgamma(vp1) * zetp(vp1);
          };
          last_interval(reflec, notdone, r, x);
        }
      }
      return r;
    }
  }
}
