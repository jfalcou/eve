//==================================================================================================
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
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special/regular/lbeta.hpp>
#include <eve/module/special/regular/signgam.hpp>
#include <eve/traits/common_value.hpp>

namespace eve
{
template<typename Options>
struct betainc_t : elementwise_callable<betainc_t, Options>
{
  template<eve::floating_value T0, eve::floating_value T1, eve::floating_value T2>
  requires (same_lanes_or_scalar<T0, T1, T2>)
  constexpr EVE_FORCEINLINE eve::common_value_t<T0, T1, T2>
  operator()(T0 a, T1 b, T2 c) const noexcept
  { return EVE_DISPATCH_CALL(a, b, c); }

  EVE_CALLABLE_OBJECT(betainc_t, betainc_);
};

//================================================================================================
//! @addtogroup special
//! @{
//!   @var betainc
//!   @brief Computes the betainc incomplete function. \f$\displaystyle \mbox{I}_s(x,y) =
//!   \frac{1}{\mbox{B}(x,y)}\int_0^s t^{x-1}(1-t)^{y-1}\mbox{d}t\f$
//!
//!   **Defined in header**
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
//!      constexpr auto betainc(floating_value auto s,
//!                             floating_value auto x, floating_value auto y)    noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto betainc[conditional_expr auto c](floating_value auto s,
//!                             floating_value auto x, floating_value auto y)    noexcept; // 2
//!      constexpr auto betainc[logical_value auto m](floating_value auto s,
//!                             floating_value auto x, floating_value auto y)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `s` :  [real floating argument](@ref eve::floating_value). \f$ s \in [0, 1]\f$
//!
//!     * `x`, `y`:  [strictly positive real floating arguments](@ref eve::floating_value).
//!
//!   **Return value**
//!
//!   The value of the incomplete betainc function is returned.
//!
//!  @groupheader{External references}
//!   *  [DLMF: Incomplete Beta Function](https://dlmf.nist.gov/8.17)
//!   *  [Wolfram MathWorld: Beta Incomplete Function](https://mathworld.wolfram.com/IncompleteBetaFunction.html)
//!   *  [Wikipedia: Beta Function](https://en.wikipedia.org/wiki/Beta_function)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/special/betainc.cpp}
//================================================================================================
 inline constexpr auto betainc = functor<betainc_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template< typename T, callable_options O>
    constexpr EVE_FORCEINLINE
    auto betainc_(EVE_REQUIRES(cpu_), O const&, T px, T pa, T pb) noexcept
    {
      auto betacf = [](auto x, auto a, auto b) {
        // continued fraction for incomplete Beta function, used by betainc
        constexpr std::size_t itmax = 100;
        auto const            o     = one(as(x));
        auto                  epsi  = 10 * eps(as(x));
        auto                  fpmin = sqr(eps(as(x)));
        auto                  qab   = a + b;
        auto                  qap   = inc(a);
        auto                  qam   = dec(a);
        auto                  c     = o;
        auto                  d     = rec[pedantic](maxmag(oneminus(qab * x / qap), fpmin));
        auto                  h     = d;
        for( std::size_t m = 1; m <= itmax; ++m )
        {
          T    vm(m);
          auto vm2 = vm + vm;
          auto aa  = vm * (b - vm) * x / ((qam + vm2) * (a + vm2));
          d        = rec[pedantic](maxmag(fma(aa, d, o), fpmin));
          c        = maxmag(fma(aa, rec[pedantic](c), o), fpmin);
          h *= d * c;
          aa       = -(a + vm) * (qab + vm) * x / ((a + vm2) * (qap + vm2));
          d        = rec[pedantic](maxmag(fma(aa, d, o), fpmin));
          c        = maxmag(fma(aa, rec[pedantic](c), o), fpmin);
          auto del = d * c;
          h *= del;
          if( eve::all(eve::abs(oneminus(del)) < epsi) ) return h; // Are we done?
        }
        return h;
      };
      auto bt   = exp(fma(pa, log(px), pb * log1p(-px)) - lbeta(pa, pb));
      auto test = (px > inc(pa) / (pa + pb + T(2)));
      auto oms   = oneminus[test](px);
      swap_if(test, pa, pb);
      auto res  = bt * betacf(oms, pa, pb) / pa;
      return if_else(is_ltz(oms) || oms > one(as(px)),
                     allbits,
                     if_else(is_eqz(oms), zero, if_else(px == one(as(px)), one, oneminus[test](res))));
    }
  }
}
