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
#include <eve/module/math/regular/sinpi.hpp>

namespace eve
{
  template<typename Options>
  struct sind_t : elementwise_callable<sind_t, Options, quarter_circle_option, half_circle_option,
                                       full_circle_option, medium_option, big_option>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sind_t, sind_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var sind
//!
//! @brief Callable object computing the sine from an input in degrees.
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
//!      T sind(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) sine of the input expressed in degrees.
//!
//! In particular:
//!
//!   * If the element is \f$\pm0\f$, \f$1\f$ is returned.
//!   * If the element is \f$\pm\infty\f$, Nan is returned.
//!   * If the element is a `NaN`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/sind.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::quarter_circle, eve::half_circle, eve::full_circle,
//!
//!     provide a balance between speed and range limitation.
//!
//!  @}
//================================================================================================
  inline constexpr auto sind = functor<sind_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T sind_(EVE_REQUIRES(cpu_), O const& , T const& a0)
    {
      auto x = eve::abs(a0);
      if constexpr(O::contains(quarter_circle2))
      {
       if( eve::all(eve::abs(x) <= T(45)) ) return  sinpi[eve::quarter_circle2](div_180(a0));
        else return sind[big2](a0);
      }
      else if constexpr(O::contains(half_circle2) || O::contains(full_circle2)
                        ||  O::contains(medium2) || O::contains(big2))
      {
        if constexpr( scalar_value<T> )
          if( is_not_finite(a0) ) return nan(eve::as<T>());
         x                  = if_else(is_not_finite(x), eve::allbits, x); // nan or Inf input
        auto [fn, xr, dxr] = rem180(x);
        return sin_finalize(bitofsign(a0), fn, xr, dxr);
      }
      else
      {
        if( eve::all(eve::abs(x) <= T(45)) )
          return sind[quarter_circle2](a0);
        else
          return sind[big2](a0);
      }
    }
  }
}
