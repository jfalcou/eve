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
//! @brief `elementwise_callable` object computing the cotangent from an input in \f$\pi\f$ multiples.
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
//!      constexpr auto cotpi(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto cotpi[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto cotpi[logical_value auto m](floating_value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto cotpi[quarter_circle](floating_value auto x)          noexcept; // 3.a
//!      constexpr auto cotpi[half_circle](floating_value auto x)             noexcept; // 3.b
//!      constexpr auto cotpi[full_circle](floating_value auto x)             noexcept; // 3.c
//!   }
//!   @endcode
//!
//! **Parameters**
///!
//!     * `x`: [floating value](@ref floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//! **Return value**
//!
//!    1.   Returns the [elementwise](@ref glossary_elementwise) cosine of the input in \f$\pi\f$ multiples.
//!       The call `cospi(x)` is semantically equivalent to \f$\cos(\pi x)\f$.
//!       In particular:
//!        * If the element is \f$\pm0\f$, \f$\pm\infty\f$ is returned.
//!        * If the element is \f$\pm1/2\f$, \f$0\f$ is returned.
//!        * If the element is \f$\pm\infty\f$, Nan is returned.
//!        * If the element is a `Nan`, `Nan` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!    3. These are optimized calls providing a balance between speed and range limitation.
//!        1. assumes that the inputs elements  belong to \f$[-1/4,1/4]\f$ and return NaN outside.
//!        2. assumes that the inputs elements  belong to \f$[-1/2,1/2]\f$ and return NaN outside.
//!        3. assumes that the inputs elements  belong to \f$[-1,1]\f$ and return NaN outside.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/cotpi.cpp}
//================================================================================================
  inline constexpr auto cotpi = functor<cotpi_t>;
//================================================================================================
//!  @}
//================================================================================================

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
