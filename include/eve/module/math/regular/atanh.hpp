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
#include <eve/module/core.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/math/regular/log1p.hpp>

namespace eve
{
  template<typename Options>
  struct atanh_t : elementwise_callable<atanh_t, Options>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(atanh_t, atanh_);
  };

//================================================================================================
//! @addtogroup math_invhyper
//! @{
//! @var atanh
//!
//! @brief Callable object computing \f$\frac{1}{2}\log((1+x)/(1-x))\f$.
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
//!      T atanh(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//!   *   Returns the [elementwise](@ref glossary_elementwise) inverse hyperbolic cotangent of the input.
//!       The inverse hyperbolic sine is semantically equivalent to \f$\frac{1}{2}\log((1+x)/(1-x))\f$.
//!
//!       In particular:
//!
//!         * If the element is \f$\pm1\f$, \f$\pm\infty\f$ is returned.
//!         * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!         * If the element is greater than one or a `NaN`, `NaN` is returned.
//!
//!         * for every z: eve::atanh(eve::conj(z)) == eve::conj(std::atanh(z))
//!         * for every z: eve::atanh(-z) == -eve::atanh(z)
//!         * If z is \f$+0\f$, the result is \f$+0\f$
//!         * If z is \f$NaN\f$, the result is \f$NaN\f$
//!         * If z is \f$+1\f$, the result is \f$+\infty\f$
//!         * If z is \f$x+i \infty\f$ (for any finite positive x), the result is \f$+0,\pi/2\f$
//!         * If z is \f$x+i NaN\f$ (for any finite nonzero x),  the result is \f$NaN+i NaN\f$
//!         * If z is \f$+\infty+i y\f$ (for any finite positive y),  the result is \f$i \pi/2\f$
//!         * If z is \f$+\infty+i \infty\f$, the result is \f$i \pi/2\f$
//!         * If z is \f$+\infty+i NaN\f$,  the result is \f$i NaN\f$
//!         * If z is \f$NaN+i y\f$ (for any finite y), the result is \f$NaN+i NaN\f$
//!         * If z is \f$NaN+i \infty\f$, the result is \f$i \pi/2\f$ (the sign of the real part is unspecified)
//!         * If z is \f$NaN+i NaN\f$,  the result is \f$NaN+i NaN\f$
//!
//!  @groupheader{Example}
//!
//!   @godbolt{doc/math/regular/atanh.cpp}
//!
//!  @}
//================================================================================================
 inline constexpr auto atanh = functor<atanh_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T atanh_(EVE_REQUIRES(cpu_), O const& , T const& x)
    {
      auto absx = eve::abs(x);
      auto t    = absx + absx;
      auto z1   = oneminus(absx);
      auto test = absx < half(eve::as<T>());
      auto tmp  = if_else(test, absx, t) / z1;
      if constexpr( scalar_value<T> ) tmp = test ? fma(t, tmp, t) : tmp;
      else tmp = fma[test](tmp, t, t);
      return signnz(x)*half(eve::as<T>())*log1p(tmp);
    }
  }
}
