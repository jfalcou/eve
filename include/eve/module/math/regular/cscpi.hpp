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
#include <eve/module/math/regular/csc.hpp>

namespace eve
{
  template<typename Options>
  struct cscpi_t : elementwise_callable<cscpi_t, Options, quarter_circle_option, half_circle_option,
             full_circle_option, medium_option, big_option>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(cscpi_t, cscpi_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var cscpi
//!
//! @brief Callable object computing the cosecant in \f$\pi\f$ multiples.
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
//!      T cscpi(T x) noexcept;

//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!
//!
//! **Return value**
//!
//!   *  Returns the [elementwise](@ref glossary_elementwise) cosecant of the input expressed in
//!      \f$\pi\f$ multiples.
//!
//!      The call `cscpi(x)` is semantically equivalent to \f$\csc(\pi x)\f$.
//!      In particular:
//!
//!      * If the element is \f$\pm0\f$, \f$\pm\infty\f$ is returned.
//!      * If the element is \f$\pm\infty\f$, Nan is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/cscpi.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::quarter_circle, eve::half_circle, eve::full_circle,
//!
//!     provide a balance between speed and range limitation.
//!
//!  @}
//================================================================================================
  inline constexpr auto cscpi = functor<cscpi_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T cscpi_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      if constexpr(O::contains(quarter_circle2))
        return csc[quarter_circle2](a0 * pi(eve::as<T>()));
      else
      {
        if constexpr( scalar_value<T> )
        {
          if( is_eqz(a0) ) return rec[pedantic2](a0);
          if( is_flint(a0) || is_not_finite(a0) ) return nan(eve::as<T>()); // nan or Inf input
        }
        T x = abs(a0);
        if constexpr( simd_value<T> )
        {
          x = if_else(is_nez(a0) && (is_not_finite(x) || is_flint(x)), eve::allbits, x);
        }
        auto [fn, xr, dxr] = rem2(x);
        return rec[pedantic2](sin_finalize(bitofsign(a0), quadrant(fn), xr, dxr));
      }
    }
  }
}
