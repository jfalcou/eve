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
  struct sindcosd_t : elementwise_callable< sindcosd_t, Options
                                          , quarter_circle_option, half_circle_option
                                          , full_circle_option, medium_option, big_option
                                          >
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE zipped<T,T> operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sindcosd_t, sindcosd_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var sindcosd
//!
//! @brief Callable object computing the simultaneous  computation of sine an cosine
//! from an argument in degrees.
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
//!      zipped<T,T> sindcosd(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//! The computation returns a pair and is semantically equivalent to `{sind(x), cosd(x)}`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/sindcosd.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::quarter_circle, eve::half_circle, eve::full_circle,
//!
//!     provide a balance between speed and range limitation.
//!
//!  @}
//================================================================================================
 inline constexpr auto sindcosd = functor<sindcosd_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE auto
    sindcosd_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      if constexpr(O::contains(quarter_circle2))
      {
        return sinpicospi[eve::quarter_circle](div_180(a0));
      }
      else if constexpr(O::contains(big2) )
      {
        if constexpr( scalar_value<T> )
          if( is_not_finite(a0) ) return eve::zip(nan(eve::as<T>()), nan(eve::as<T>()));
        auto x             = eve::abs(a0);
        x                  = if_else(is_not_finite(x), eve::allbits, x); // nan or Inf input
        auto [fn, xr, dxr] = rem180(x);
        auto[s,c] = sincos_finalize(bitofsign(a0), fn, xr, dxr);
        return eve::zip(s,c);
      }
      else
      {
        if( eve::all(eve::abs(a0) <= T(45)) ) return sindcosd[quarter_circle2](a0);
        else                                  return sindcosd[big2](a0);
      }
    }
  }
}
