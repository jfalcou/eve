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
  struct cospi_t : elementwise_callable<cospi_t, Options, quarter_circle_option, half_circle_option,
                                        full_circle_option, medium_option, big_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(cospi_t, cospi_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var cospi
//!
//! @brief Callable object computing the cosine from an input in \f$\pi\f$ multiples.
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
//!      T cospi(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!
//! **Return value**
//!
//!   *   Returns the [elementwise](@ref glossary_elementwise) cosine of the input.
//!       The call `cospi(x)` is semantically equivalent to \f$\cos(\pi x)\f$.
//!
//!       In particular:
//!
//!        * If the element is \f$\pm0\f$, \f$1\f$ is returned.
//!        * If the element is \f$\pm1/2\f$, \f$0\f$ is returned.
//!        * If the element is \f$\pm\infty\f$, Nan is returned.
//!        * If the element is a `Nan`, `Nan` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/cospi.cpp}
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
 inline constexpr auto cospi = functor<cospi_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T cospi_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      if constexpr(floating_value<T>)
      {
        if constexpr(O::contains(half_circle2) || O::contains(full_circle2)
                     ||  O::contains(medium2) || O::contains(big2))
        {
          if constexpr( scalar_value<T> )
            if( is_not_finite(a0) ) return nan(eve::as<T>());
          auto x = eve::abs(a0);
          if constexpr( scalar_value<T> )
          {
            if( x > maxflint(eve::as<T>()) ) return T(1);
          }
          else
          {
            x = if_else(is_not_finite(x), eve::allbits, x); // nan or Inf input
            x = if_else(is_greater(x, maxflint(eve::as(x))), eve::zero, x);
          }
          auto [fn, xr, dxr] = rem2(x);
          return cos_finalize(fn, xr, dxr);
        }
        else if constexpr(O::contains(quarter_circle2))
        {
          return eve::cos[quarter_circle2](a0*pi(eve::as<T>()));
        }
        else
        {
          auto x = abs(a0);
          if( eve::all(eve::abs(x) <= T(0.25)) )
            return cospi[quarter_circle2](x);
          else
            return cospi[big2](x);
        }
      }
      else
      {
        return if_else(is_odd(a0), eve::mone, one(eve::as(a0))); //(-1)^n
      }
    }
  }
}
