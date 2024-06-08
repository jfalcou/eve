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
#include <eve/module/math/constant/pi.hpp>
#include <eve/module/math/decorator/trigo_tags.hpp>
#include <eve/module/math/detail/generic/rem2.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>

namespace eve
{
  template<typename Options>
  struct cotpi_t : elementwise_callable<cotpi_t, Options, quarter_circle_option, half_circle_option,
                                        full_circle_option, medium_option, big_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(cotpi_t, cotpi_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var cotpi
//!
//! @brief Callable object computing the arc cotangent from an input in \f$\pi\f$ multiples.
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
//!      T cotpi(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!
//! **Return value**
//!
//!   *  Returns the [elementwise](@ref glossary_elementwise) cotangent of the input expressed in \f$\pi\f$
//!      multiples. In particular:
//!
//!      * If the element is \f$\pm0\f$, \f$\pm\infty\f$ is returned.
//!      * If the element is \f$\pm\infty\f$, Nan is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/cotpi.cpp}
//!
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::quarter_circle, eve::half_circle, eve::full_circle,
//!
//!     provide a balance between speed and range limitation.
//!
//!  @}
//================================================================================================
  inline constexpr auto cotpi = functor<cotpi_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T cotpi_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      if constexpr(O::contains(quarter_circle2))
      {
        if constexpr( scalar_value<T> )
        {
          if( is_eqz(a0) ) return bit_or(a0, inf(eve::as(a0)));
          auto x = abs(a0);
          if( is_not_less_equal(x, T(0.25)) ) return nan(eve::as<T>());
          return rec[pedantic2](tancot_eval(pi(eve::as<T>()) * a0));
        }
        else
        {
          auto x = eve::abs(a0);
          return if_else(is_eqz(a0),
                         bit_or(a0, inf(eve::as(a0))),
                         if_else(is_not_less_equal(x, T(0.25)),
                                 eve::allbits,
                                 rec[pedantic2](tancot_eval(pi(eve::as<T>()) * a0))));
        }
      }
      else if constexpr(O::contains(half_circle2) || O::contains(full_circle2)
                   ||  O::contains(medium2) || O::contains(big2))
      {
        if constexpr( scalar_value<T> )
        {
          if( is_eqz(a0) ) return bit_or(a0, inf(eve::as(a0)));
          if( is_not_finite(a0) || is_flint(a0) ) return nan(eve::as<T>());
        }
        auto x = abs(a0);
        if constexpr( simd_value<T> )
        {
          x = if_else(is_not_finite(a0) || is_flint(x), eve::allbits, x);
        }
        auto [fn, xr, dxr] = rem2(x);
        return cot_finalize(a0 * pi(eve::as<T>()), quadrant(fn), xr, dxr);
      }
      else
      {
        if( eve::all(eve::abs(a0) <= T(0.25)) )
          return cotpi[quarter_circle2](a0);
        else return cotpi[big2](a0);
      }
    }
  }
}
