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
#include <eve/module/math/decorator/trigo_tags.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>
#include <eve/module/math/regular/deginrad.hpp>
#include <eve/module/math/regular/div_180.hpp>
#include <eve/module/math/regular/tanpi.hpp>

namespace eve
{
  template<typename Options>
  struct tand_t : elementwise_callable<tand_t, Options, quarter_circle_option, half_circle_option,
                                        full_circle_option, medium_option, big_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(tand_t, tand_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var tand
//!
//! @brief Callable object computing the tangent from an input in degrees.
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
//!      T tand(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) tangent of the input expressed in
//! degrees.
//!
//! In particular:
//!
//!   * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!   * If the element is \f$\pm\infty\f$, Nan is returned.
//!   * If the element is a `NaN`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/tand.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::quarter_circle, eve::half_circle, eve::full_circle,
//!
//!     provide a balance between speed and range limitation.
//!
//!  @}
//================================================================================================
  inline constexpr auto tand = functor<tand_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T tand_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      if constexpr(O::contains(half_circle2) || O::contains(full_circle2)
                   ||  O::contains(medium2) || O::contains(big2))
      {
        auto x      = eve::abs(a0);
        auto a0_180 = div_180(a0);
        auto test   = is_not_flint(a0_180) && is_flint(a0_180 + mhalf(eve::as(a0_180)));
        if constexpr( scalar_value<T> )
        {
          if( is_eqz(a0) ) return a0;
          if( test ) return nan(eve::as<T>());
        }
        else
          x = if_else(test, eve::allbits, x);
        auto [fn, xr, dxr] = rem180(x);
        return tan_finalize(deginrad(a0), fn, xr, dxr);
      }
      else if constexpr(O::contains(quarter_circle2))
      {
        return tanpi[eve::quarter_circle](div_180(a0));
      }
      else
      {
        auto x = abs(a0);
        if( eve::all(eve::abs(x) <= T(45)) ) return tand[eve::quarter_circle2](a0);
        else return tand[big2](a0);
      }
    }
  }
}
