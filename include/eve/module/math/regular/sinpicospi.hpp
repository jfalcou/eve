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
#include <eve/module/math/constant/pi2o_16.hpp>
#include <eve/module/math/constant/pio_2.hpp>
#include <eve/module/math/constant/pio_4.hpp>
#include <eve/module/math/decorator/trigo_tags.hpp>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>
#include <eve/module/math/regular/rempio2.hpp>
#include <eve/module/math/regular/sinpicospi.hpp>

namespace eve
{
  template<typename Options>
  struct sinpicospi_t : elementwise_callable< sinpicospi_t, Options
                                            , quarter_circle_option, half_circle_option
                                            , full_circle_option, medium_option, big_option
                                            >
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE zipped<T,T> operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sinpicospi_t, sinpicospi_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var sinpicospi
//!
//! @brief Callable object computing the simultaneous  computation of sin an cos from
//! an argument in \f$\pi\f$ multiples.
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
//!      zipped<T,T> sinpicospi(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!
//! **Return value**
//!
//! The computation returns a pair and is semantically equivalent to `{sinpi(x), cospi(x)}`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/sinpicospi.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::quarter_circle, eve::half_circle, eve::full_circle,
//!
//!     provide a balance between speed and range limitation.
//!
//!  @}
//================================================================================================
 inline constexpr auto sinpicospi = functor<sinpicospi_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE auto
    sinpicospi_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      if constexpr(O::contains(quarter_circle2))
      {
        return sincos[eve::quarter_circle](a0 * pi(eve::as<T>()));
      }
      else if constexpr( O::contains(big2) )
      {
        if constexpr( scalar_value<T> )
        {
          if( is_not_finite(a0) ) return eve::zip(nan(eve::as<T>()), nan(eve::as<T>()));
        }
        T x = abs(a0);
        if constexpr( scalar_value<T> )
        {
          if( x > maxflint(eve::as<T>()) ) return eve::zip(T(0), T(1));
        }
        else
        {
          auto invalid = is_not_finite(x);
          x            = if_else(x > maxflint(eve::as(x)), eve::zero, x);
          x            = if_else(invalid, eve::allbits, x);
        }
        auto [fn, xr, dxr] = rem2(x);
        auto [s, c]        = sincos_finalize(bitofsign(a0), fn, xr, dxr);
        return eve::zip(s, c);
      }
      else
      {
        auto x = abs(a0);
        if( eve::all(x <= T(0.25)) )  return sinpicospi[quarter_circle2](a0);
        else  return sinpicospi[big2](a0);
      }
    }
  }
}
