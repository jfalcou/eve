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
#include <eve/module/math/regular/exp.hpp>
#include <eve/module/math/constant/log_2.hpp>
#include <eve/module/math/constant/maxlog.hpp>

namespace eve
{
  template<typename Options>
  struct sech_t : elementwise_callable<sech_t, Options>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sech_t, sech_);
  };

//================================================================================================
//! @addtogroup math_hyper
//! @{
//! @var sech
//!
//! @brief Callable object computing \f$\frac2{e^x-e^{-x}}\f$.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T >
//!      T sech(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!
//! **Return value**
//!
//!   *  Returns the [elementwise](@ref glossary_elementwise) hyperbolic secant of the input.
//!
//!      In particular:
//!
//!      * If the element is \f$\pm0\f$, 1 is returned.
//!      * If the element is \f$\pm\infty\f$, \f$+0\f$ is returned.
//!      * If the element is a `NaN`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/sech.cpp}
//!  @}
//================================================================================================
  inline constexpr auto sech = functor<sech_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T sech_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      //////////////////////////////////////////////////////////////////////////////
      // if x = abs(a0) according x < Threshold e =  exp(x) or exp(x/2) is
      // respectively computed
      // *  in the first case sech (e+rec[pedantic2](e))/2
      // *  in the second     sech is (e/2)*e (avoiding undue overflow)
      // Threshold is maxlog - Log_2
      //////////////////////////////////////////////////////////////////////////////
      T    x     = eve::abs(a0);
      auto test1 = (x > maxlog(eve::as<T>()) - log_2(eve::as<T>()));
      auto fac   = if_else(test1, half(eve::as<T>()), eve::one);
      T    tmp1  = exp(-x * fac);
      T    tmp   = T(2) * tmp1;
      if constexpr( scalar_value<T> ) { return test1 ? tmp1 * tmp : tmp / fma(tmp1, tmp1, T(1)); }
      else { return if_else(test1, tmp1 * tmp, tmp / fma(tmp1, tmp1, T(1))); }
    }
  }
}
