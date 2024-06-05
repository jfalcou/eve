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
#include <eve/module/math/regular/sind.hpp>

namespace eve
{
  template<typename Options>
  struct cscd_t : elementwise_callable<cscd_t, Options, quarter_circle_option, half_circle_option,
             full_circle_option, medium_option, big_option>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(cscd_t, cscd_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var cscd
//!
//! @brief Callable object computing the cosecant from an input in degree.
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
//!      T cscd(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) cosecant of the input.
//! expressed in degree (the inverse of the sine)
//!
//! In particular:
//!
//!   * If the element is \f$\pm0\f$, \f$\pm\infty\f$ is returned.
//!   * If the element is \f$\pm\infty\f$, Nan is returned.
//!   * If the element is a `NaN`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/cscd.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::quarter_circle, eve::half_circle, eve::full_circle,
//!
//!     provide a balance between speed and range limitation.
//!
//!  @}
//================================================================================================
  inline constexpr auto cscd = functor<cscd_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T cscd_(EVE_REQUIRES(cpu_), O const& o, T const& a0)
    {
      if constexpr(O::contains(quarter_circle2))
        return eve::rec[pedantic2](eve::sind[o](a0));
      else
      {
        auto a0_180 = div_180(a0);
        auto test   = is_nez(a0_180) && is_flint(a0_180);
        if constexpr( scalar_value<T> ) // early return for nans in scalar case
        {
          if( test ) return nan(eve::as<T>());
        }
        return if_else(test, eve::allbits, rec[pedantic2](sind[o](a0)));
      }
    }
  }
}
