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
#include <eve/module/math/constant/inv_2eps.hpp>
#include <eve/module/math/constant/log_2.hpp>
#include <eve/module/math/regular/log.hpp>
#include <eve/module/math/regular/log1p.hpp>

namespace eve
{
  template<typename Options>
  struct acosh_t : elementwise_callable<acosh_t, Options>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(acosh_t, acosh_);
};

//================================================================================================
//! @addtogroup math_invhyper
//! @{
//! @var acosh
//!
//! @brief Callable object computing  \f$\log(x+\sqrt{x^2-1})\f$.
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
//!      template< eve::floating_value T > T acosh(T x) noexcept;
//!
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//!   * Returns the [elementwise](@ref glossary_elementwise) inverse hyperbolic cosine of the input.
//!      For values in the domain `x>1`, the inverse hyperbolic cosine is semantically equivalent to
//!      \f$\log(x+\sqrt{x^2-1})\f$.
//!
//!      In particular:
//!
//!      * If the element is less than \f$1\f$ or `Nan`, `NaN` is returned.
//!      * If the element is \f$1\f$, \f$+0\f$ is returned.
//!      * If the element is \f$+\infty\f$, \f$+\infty\f$ is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/acosh.cpp}
//!
//!  @}
//================================================================================================
  inline constexpr auto acosh = functor<acosh_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T acosh_(EVE_REQUIRES(cpu_), O const&o, T const& x)
    {
      const T    t    = dec(x);
      auto const test = is_greater(t, inv_2eps(eve::as<T>()));

      if constexpr( simd_value<T> )
      {
        const T z = if_else(test, x, t + sqrt(fma(t, t, t + t)));
        return add[test](log1p(z), log_2(eve::as<T>()));
      }
      else if constexpr( scalar_value<T> )
      {
        if( test ) { return eve::log(t) + log_2(eve::as<T>()); }
        else { return eve::log1p(t + eve::sqrt(fma(t, t, t + t))); }
      }
    }
  }
}
