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
#include <eve/detail/hz_device.hpp>
#include <eve/module/math/regular/horner.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special/regular/log_abs_gamma.hpp>

namespace eve
{
template<typename Options>
struct trigamma_t : elementwise_callable<trigamma_t, Options>
{
  template<eve::floating_value T>
  constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(trigamma_t, trigamma_);
};

//================================================================================================
//! @addtogroup special
//! @{
//!   @var trigamma
//!   @brief `elementwise_callable` object computing the Trigamma function i.e.
//!   the second derivative of the \f$\log\Gamma\f$  function.
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
//!      constexpr auto trigamma(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto trigamma[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto trigamma[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [floating_value](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. The value of the Trigamma function: \f$\psi(x) = \frac{\Gamma'(x)}{\Gamma(x)}\f$ is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [DLMF: Gamma and Psi Functions](https://dlmf.nist.gov/5.2#i)
//!   *  [Wolfram MathWorld: Trigamma Function](https://mathworld.wolfram.com/TrigammaFunction.html)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/special/trigamma.cpp}
//================================================================================================
  inline constexpr auto trigamma = functor<trigamma_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr T  trigamma_(EVE_REQUIRES(cpu_), O const&, T x) noexcept
    {
      using elt_t  = element_type_t<T>;
      auto br_small =  [](auto x){
        return rec(sqr(x));
      };

      auto br_neg =  [](auto x){
        x = if_else(is_gtz(x), one, x);
        return eve::pi2(as(x))*eve::sqr(cscpi(x))-trigamma(eve::oneminus(x));
      };

      auto br_else =  [](auto x){
        elt_t  b = 10.0;
        auto value = eve::zero(as(x));
        int n = eve::maximum(if_else(x > b, eve::zero, eve::floor(b-x)));

        for(int i=n; i >= 0 ; --i)
        {
          value += eve::rec(eve::sqr(x+i));
        }

       x+= n+1;
        elt_t  b2 =  0.1666666667;
        elt_t  b4 = -0.03333333333;
        elt_t  b6 =  0.02380952381;
        elt_t  b8 = -0.03333333333;
        elt_t  b10=  7.575757575757576e-02;
        auto y = eve::rec(eve::sqr(x));
        value +=  eve::half(as(x))*y + eve::reverse_horner(y, elt_t(1), b2, b4, b6, b8, b10)*rec(x);
        return value;
      };


      auto r       = nan(as<T>());                      // nan and zero case treated here
      r            = if_else(x == inf(as(x)), zero, r);
      auto notdone = eve::is_nez(x) && eve::is_not_nan(x) && (x != inf(as(x)));

      if( eve::any(notdone) )
      {
        notdone = next_interval(br_neg, notdone, eve::is_ltz(x), r, x);
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_small, notdone, x < T(1.0e-4), r, x);
          if( eve::any(notdone) )
          {
            notdone = last_interval(br_else, notdone, r, x);
          }
        }
      }
      return r;
    }
  }
}
