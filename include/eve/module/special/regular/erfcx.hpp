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
#include <eve/module/math/regular/horner.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special/detail/erf_kernel.hpp>

namespace eve
{
  template<typename Options>
  struct erfcx_t : elementwise_callable<erfcx_t, Options>
  {
    template<eve::floating_ordered_value T>
    EVE_FORCEINLINE constexpr T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(erfcx_t, erfcx_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var erfcx
//!   @brief Computes the normalized complementary error function
//!   \f$ \displaystyle \mbox{erfcx}(x) = e^{x^2} \mbox{erfc}(x)\f$.
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
//!      template< eve::floating_ordered_value T >
//!      T erfcx(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!   The value of the normalized complementary error function is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/special/regular/erfcx.cpp}
//! @}
//================================================================================================
inline constexpr auto erfcx = functor<erfcx_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr T
    erfcx_(EVE_REQUIRES(cpu_), O const&, T x) noexcept
    {
      /*
       * Based on: M. M. Shepherd and J. G. Laframboise, "Chebyshev Approximation of
       * (1+2x)exp(x^2)erfc x in 0 <= x < INF", Mathematics of Computation, Vol. 36,
       * No. 153, January 1981, pp. 249-253.
       *
       */
      if constexpr( scalar_value<T> && eve::platform::supports_invalids )
      {
        if( is_nan(x) ) return x;
      }
      using elt_t     = element_type_t<T>;
      auto largelimit = [](){
        // for x greater than the value 1/(sqrt(pi)*x) ==  erfcx(x) at working precision
        if constexpr( std::is_same_v<elt_t, float> ) return 0x1.a919d2p+37;
        else return 0x1.fffffffffffffp+510;
      };
      auto    ll        = largelimit();
      const T invsqrtpi = T(0.564189583547756286948079451560772585844050629329);
      T       a         = eve::abs(x);
      if constexpr( scalar_value<T> )
      {
        if( x == inf(as(x)) ) return zero(as(a));
        if( x > ll ) return invsqrtpi * rec[pedantic2](a);
        auto largeneglimit = [](){
          // for x less than the value erfcx(x) is inf at working precision
          if constexpr( std::is_same_v<elt_t, float> ) return -0x1.fffffcp+63;
          else return -0x1.ffffffffffffep+511;
        };
        if( x < largeneglimit() ) return inf(as(a));
      }
      constexpr auto isfloat = std::same_as<elt_t, float>;
      const T        shift   = if_else(isfloat, T(2), T(4));
      /* Compute q = (a-shift)/(a+shift) accurately. [0,INF) -> [-1,1] */
      T    m = a - shift;
      T    p = a + shift;
      auto r = rec[pedantic2](p);
      T    q = m * r;
      T    t = fnma(inc(q), shift, a);
      T    e = fma(q, -a, t);
      q      = fma(r, e, q);
      /* Approximate (1+2*a)*exp(a*a)*erfc(a) as p(q)+1 for q in [-1,1] */
      if constexpr( isfloat )
      {
        p = eve::reverse_horner(q, T(0x1.1ba03ap-2f), T(-0x1.7bf5cep-4f), T(-0x1.54081ap-3f)
                               , T(0x1.4ff8acp-3f), T(-0x1.bc1b6cp-5f), T(-0x1.069940p-7f)
                               , T(0x1.1cc236p-7f), T(0x1.3c1d7ep-10f), T(-0x1.6e2a7cp-10f)
                               , T(-0x1.6b4ffep-12f), T(0x1.521cc6p-13f), T(0x1.f10000p-15f));
      }
      else // isdouble
      {
        p = eve::reverse_horner(q, T(0x1.dd2c8b74febf6p-3), T(-0x1.1df1ad154a27fp-3), T(0x1.f7f5df66fc349p-7)
                               , T(0x1.16ecefcfa4865p-4), T(-0x1.9ddb23c3e14d2p-4), T(0x1.7fee004e266dfp-4)
                               , T(-0x1.0fb06dfedc4ccp-4), T(0x1.3079edf465cc3p-5), T(-0x1.0962386ea02b7p-6)
                               , T(0x1.49c673066c831p-8), T(-0x1.8d4aaa0099bc8p-11), T(-0x1.a1df71176b791p-13)
                               , T(0x1.3be1255ce180bp-13), T(-0x1.9951f39295cf4p-16), T(-0x1.78a680a741c4ap-17)
                               , T(0x1.7eec072bb0be3p-18), T(0x1.3fef1358803b7p-22), T(-0x1.b87373facb29fp-21)
                               , T(0x1.31c2b2b44b731p-24), T(0x1.c6a8093ac4f83p-24), T(-0x1.1985b48f08574p-26)
                               , T(-0x1.a1ad2e6c4a7a8p-27), T(0x1.b1548f14735d1p-30), T(0x1.edcad78fc8044p-31));
      }

      /* Divide (1+p) by (1+2*a) ==> exp(a*a)*erfc(a) */
      T d = a + half(as<T>());
      r   = rec[pedantic2](d);
      r *= half(as<T>());
      q = fma(p, r, r);
      t = q + q;
      e = (p - q) + fma(t, -a, T(1));
      r = fma(e, r, q);
      if( eve::any(a > ll) ) r = if_else(a > ll, invsqrtpi * rec[pedantic2](a), r);
      auto xpos = (x >= 0);
      if( eve::all(xpos) ) return r;
      /* Handle negative arguments: erfcx(x) = 2*exp(x*x) - erfcx(|x|) */
      auto r1 = fms(T(2), expx2(x), r);
      r1      = if_else(is_nan(r1), inf(as<T>()), r1);
      r       = if_else(xpos, r, r1);
      return if_else(is_nan(x), eve::allbits, r);
    }
  }
}
