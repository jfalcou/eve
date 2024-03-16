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
#include <eve/module/math/regular/cos.hpp>
#include <eve/module/math/detail/generic/rem2.hpp>

namespace eve
{
  template<typename Options>
  struct tanpi_t : elementwise_callable<tanpi_t, Options, quarter_circle_option, half_circle_option,
                                        full_circle_option, medium_option, big_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(tanpi_t, tanpi_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var tanpi
//!
//! @brief Callable object computing the tangent from an input in \f$\pi\f$ multiples.
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
//!      T tanpi(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!
//! **Return value**
//!
//!   *  Returns the [elementwise](@ref glossary_elementwise) tangent of the input expressed in \f$\pi\f$
//!      multiples. In particular:
//!
//!      * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!      * If the element is \f$\pm\infty\f$, Nan is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/tanpi.cpp}
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
  inline constexpr auto tanpi = functor<tanpi_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T tanpi_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      if constexpr(O::contains(half_circle2) || O::contains(full_circle2)
                   ||  O::contains(medium2) || O::contains(big2))
      {
        auto x = eve::abs(a0);
        if constexpr( scalar_value<T> )
        {
          if( is_eqz(a0) ) return a0;
          if( is_not_finite(x) || (frac(x) == half(eve::as<T>())) ) return nan(eve::as<T>());
          if( x > maxflint(eve::as<T>()) || is_flint(x) ) return T(0);
        }
        else
        {
          x = if_else(is_greater(x, maxflint(eve::as(x))) || is_flint(x), eve::zero, x);
          x = if_else(is_not_finite(a0) || (frac(x) == half(eve::as<T>())), eve::allbits, x);
        }
        auto [fn, xr, dxr] = rem2(x);
        return tan_finalize(a0 * pi(eve::as<T>()), fn, xr, dxr);
      }
      else  if constexpr(O::contains(quarter_circle2))
      {
        return tan[eve::quarter_circle2](a0 * pi(eve::as<T>()));
      }
      else
      {
        auto x = abs(a0);
        if( eve::all(eve::abs(x) <= T(0.25)) ) return tanpi[eve::quarter_circle2](a0);
        else return tanpi[big2](a0);
      }
    }
  }
}
