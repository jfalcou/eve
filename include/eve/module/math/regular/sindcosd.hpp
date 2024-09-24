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

#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>
#include <eve/module/math/regular/rempio2.hpp>
#include <eve/module/math/regular/sinpicospi.hpp>

namespace eve
{
  template<typename Options>
  struct sindcosd_t : elementwise_callable< sindcosd_t, Options, quarter_circle_option
                                          >
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE zipped<T,T> operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sindcosd_t, sindcosd_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var sindcosd
//!
//! @brief `elementwise_callable` object computing the simultaneous  computation of sine an cosine
//! from an argument in degrees.
//!
//!   @groupheader{Header file}
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
//!      // Regular overload
//!      constexpr auto sindcosd(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto sindcosd[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto sindcosd[logical_value auto m](floating_value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto sindcosd[quarter_circle](floating_value auto x)          noexcept; // 3
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!      * `x`: [floating value](@ref floating_value).
//!      * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!      * `m`: [Logical value](@ref logical) masking the operation.
//!
//! **Return value**
//!
//!   1 .The computation returns a tuple-like whose elements are `sind(x)` and `cosd(x)`
//!   2. [The operation is performed conditionnaly](@ref conditional).
//!   3. Assumes that the inputs elements  belong to \f$[-45, 45]\f$ and return NaN outside.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/sindcosd.cpp}
//================================================================================================
  inline constexpr auto sindcosd = functor<sindcosd_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE auto
    sindcosd_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      if constexpr(O::contains(quarter_circle))
      {
        return sinpicospi[eve::quarter_circle](div_180(a0));
      }
      else
      {
        if( eve::all(eve::abs(a0) <= T(45)) ) return sindcosd[quarter_circle](a0);
        if constexpr( scalar_value<T> )
          if( is_not_finite(a0) ) return eve::zip(nan(eve::as<T>()), nan(eve::as<T>()));
        auto x             = eve::abs(a0);
        x                  = if_else(is_not_finite(x), eve::allbits, x); // nan or Inf input
        auto [fn, xr, dxr] = rem180(x);
        auto[s,c] = sincos_finalize(bitofsign(a0), fn, xr, dxr);
        return eve::zip(s,c);
      }
    }
  }
}
