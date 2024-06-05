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
#include <eve/module/math/regular/expm1.hpp>

namespace eve
{
  template<typename Options>
  struct tanh_t : elementwise_callable<tanh_t, Options>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(tanh_t, tanh_);
  };

//================================================================================================
//! @addtogroup math_hyper
//! @{
//! @var tanh
//!
//! @brief Callable object computing \f$\frac{e^x-e^{-x}}{e^x+e^{-x}}\f$.
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
//!      T tanh(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//!   *  Returns the [elementwise](@ref glossary_elementwise) hyperbolic tangent of the input.
//!
//!      In particular:
//!
//!      * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!      * If the element is \f$\pm\infty\f$, \f$\pm1\f$ returned.
//!      * If the element is a `NaN`, `NaN` is returned.
//!
//!      * for every z: `eve::tanh(eve::conj(z)) == eve::conj(std::tanh(z))`
//!      * for every z: `eve::tanh(-z)           == -eve::tanh(z)`
//!      * If z is \f$+0\f$, the result is \f$+0\f$
//!      * If z is \f$x+i \infty\f$ (for any non zero finite x), the result is \f$NaN+i NaN\f$
//!      * If z is \f$i \infty\f$  the result is \f$i NaN\f$
//!      * If z is \f$x,NaN\f$ (for any non zero finite x), the result is \f$NaN+i NaN\f$
//!      * If z is \f$i NaN\f$  the result is \f$i NaN\f$
//!      * If z is \f$+\infty,y\f$ (for any finite positive y), the result is \f$1\f$
//!      * If z is \f$+\infty+i \infty\f$, the result is \f$1,\pm 0\f$ (the sign of the imaginary part is unspecified)
//!      * If z is \f$+\infty+i NaN\f$, the result is \f$1\f$ (the sign of the imaginary part is unspecified)
//!      * If z is \f$NaN\f$, the result is \f$NaN\f$
//!      * If z is \f$NaN+i y\f$ (for any non-zero y), the result is \f$NaN+i NaN\f$
//!      * If z is \f$NaN+i NaN\f$, the result is \f$NaN+i NaN\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/tanh.cpp}
//!
//!  @}
//================================================================================================
  inline constexpr auto tanh = functor<tanh_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T tanh_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      if constexpr( scalar_value<T> )
      {
        if( is_eqz(a0) ) return a0;
      }
      auto x    = eve::abs(a0 + a0);
      auto test = x > T(0.5493) * 2;
      auto t    = expm1(x);
      auto rt2  = rec[pedantic2](t + T(2));
      if constexpr( scalar_value<T> )
      {
        auto r = test ? fnma(T(2), rt2, T(1)) : t * rt2;
        return copysign(r, a0);
      }
      else if constexpr( simd_value<T> )
      {
        auto z1 = fnma(T(2), rt2, T(1));
        auto z2 = t * rt2;
        auto r  = if_else(test, z1, z2);
        return copysign(r, a0);
      }
    }
  }
}
