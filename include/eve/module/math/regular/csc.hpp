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
#include <eve/module/math/regular/sin.hpp>

namespace eve
{
  template<typename Options>
  struct csc_t : elementwise_callable<csc_t, Options, quarter_circle_option, half_circle_option,
             full_circle_option, medium_option, big_option>
  {
    template<floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(csc_t, csc_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var csc
//!
//! @brief `elementwise_callable` object computing the cosecant of the input.
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
//!      constexpr auto csc(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto csc[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto csc[logical_value auto m](floating_value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto csc[quarter_circle](floating_value auto x)          noexcept; // 3.a
//!      constexpr auto csc[half_circle](floating_value auto x)             noexcept; // 3.b
//!      constexpr auto csc[full_circle](floating_value auto x)             noexcept; // 3.c
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!      * `x`: [floating value](@ref eve::floating_value).
//!      * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!      * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!    1. Returns the [elementwise](@ref glossary_elementwise) cosecant of the input.
//!       (the inverse of the sine). In particular:
//!         * If the element is \f$\pm0\f$, \f$\pm\infty\f$ is returned.
//!         * If the element is \f$\pm\infty\f$, Nan is returned.
//!         * If the element is a `NaN`, `NaN` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!    3. These are optimized calls providing a balance between speed and range limitation.
//!        1. assumes that the inputs elements  belong to \f$[-\pi/4,\pi/4]\f$ and return NaN outside.
//!        2. assumes that the inputs elements  belong to \f$[-\pi/2,\pi/2]\f$ and return NaN outside.
//!        3. assumes that the inputs elements  belong to \f$[-\pi,\pi]\f$ and return NaN outside.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/Cosecant.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/csc.cpp}
//================================================================================================
  inline constexpr auto csc = functor<csc_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T csc_(EVE_REQUIRES(cpu_), O const& o, T const& a0)
    {
      return eve::rec[pedantic](sin[o](a0));
    }
  }
}
