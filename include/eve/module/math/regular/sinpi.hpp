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
#include <eve/module/math/regular/sin.hpp>

namespace eve
{
  template<typename Options>
  struct sinpi_t : elementwise_callable<sinpi_t, Options, quarter_circle_option, half_circle_option,
                                       full_circle_option, medium_option, big_option>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sinpi_t, sinpi_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var sinpi
//!
//! @brief Callable object computing the sine from an input in \f$\pi\f$ multiples.
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
//!      T sinpi(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!
//! **Return value**
//!
//!   *   Returns the [elementwise](@ref glossary_elementwise) sine of the input.
//!       The call `sinpi(x)` is semantically equivalent to \f$\cos(\pi x)\f$.
//!
//!       In particular:
//!
//!       * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!       * If the element is \f$\pm\infty\f$, Nan is returned.
//!       * If the element is a `Nan`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/sinpi.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::quarter_circle, eve::half_circle, eve::full_circle,
//!
//!     provide a balance between speed and range limitation.
//!
//!  @}
//================================================================================================
  inline constexpr auto sinpi = functor<sinpi_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T sinpi_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      if constexpr(O::contains(half_circle2) || O::contains(full_circle2)
                   ||  O::contains(medium2) || O::contains(big2))
      {
        if constexpr( scalar_value<T> )
          if( is_not_finite(a0) ) return nan(eve::as<T>());
        auto x = eve::abs(a0);
        if constexpr( scalar_value<T> )
        {
          if( x > maxflint(eve::as<T>()) ) return T(0);
        }
        else
        {
          x = if_else(is_not_finite(x), eve::allbits, x); // nan or Inf input
          x = if_else(is_greater(x, maxflint(eve::as(x))), eve::zero, x);
        }
        auto [fn, xr, dxr] = rem2(x);
        return sin_finalize(bitofsign(a0), fn, xr, dxr);
      }
      else if constexpr(O::contains(quarter_circle2))
      {
        return sin[eve::quarter_circle](a0 * pi(eve::as<T>()));
      }
      else
      {
        auto x = abs(a0);
        if( eve::all(eve::abs(x) <= T(0.25)) )

          return sinpi[quarter_circle2](a0);
        else
          return sinpi[big2](a0);
      }
    }
  }
}
