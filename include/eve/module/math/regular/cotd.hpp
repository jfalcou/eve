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
#include <eve/module/math/regular/cotpi.hpp>
#include <eve/module/math/regular/deginrad.hpp>
#include <eve/module/math/regular/div_180.hpp>

namespace eve
{
  template<typename Options>
  struct cotd_t : elementwise_callable<cotd_t, Options, quarter_circle_option, half_circle_option,
                                        full_circle_option, medium_option, big_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(cotd_t, cotd_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var cotd
//!
//! @brief Callable object computing cotangent from an input in degrees.
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
//!      T cotd(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) cotangent of the input expressed in
//! degrees.
//!
//! In particular:
//!
//!   * If the element is \f$\pm0\f$, \f$\pm\infty\f$ is returned.
//!   * If the element is \f$\pm\infty\f$, Nan is returned.
//!   * If the element is a `NaN`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/cotd.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::quarter_circle, eve::half_circle, eve::full_circle,
//!
//!     provide a balance between speed and range limitation.
//!
//!  @}
//================================================================================================
  inline constexpr auto cotd = functor<cotd_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T cotd_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      auto x = abs(a0);
      if constexpr(O::contains(quarter_circle2))
      {
        if constexpr( scalar_value<T> )
        {
          if( is_eqz(a0) ) return bit_or(a0, inf(eve::as(a0)));
          if( is_not_less_equal(x, T(45)) ) return nan(eve::as<T>());
          return rec[pedantic2](tancot_eval(deginrad(a0)));
        }
        else
        {
          return if_else(
            is_eqz(a0),
            bit_or(a0, inf(eve::as(a0))),
            if_else(is_not_less_equal(x, T(45)), eve::allbits, rec[pedantic2](tancot_eval(deginrad(a0)))));
        }
      }
      else if constexpr(O::contains(half_circle2) || O::contains(full_circle2)
                   ||  O::contains(medium2) || O::contains(big2))
      {
        T    a0_180 = div_180(a0);
        auto test   = is_nez(a0_180) && is_flint(a0_180);
        if constexpr( scalar_value<T> ) // early return for nans in scalar case
        {
          if( test ) return nan(eve::as<T>());
        }
        else { x = if_else(test, eve::allbits, x); }
        auto [fn, xr, dxr] = rem180(x);
        return cot_finalize(deginrad(a0), fn, xr, dxr);
      }
      else
      {
        if( eve::all(eve::abs(x) <= T(45)) )
          return cotd[quarter_circle2](a0);
        else
          return cotd[big2](a0);
      }
    }
  }
}
