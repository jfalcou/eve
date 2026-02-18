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
#include <eve/module/math/regular/asin.hpp>

namespace eve
{
  template<typename Options>
  struct asec_t : elementwise_callable<asec_t, Options, raw_option,
                                       rad_option, radpi_option, deg_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(asec_t, asec_);
};

//================================================================================================
//! @addtogroup math_invtrig
//! @{
//!   @var asec
//!   @brief Callable object computing the arc secant.
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
//!      constexpr auto asec(floating_value auto x)                          noexcept; // 1
//!
//!      // Semantic option
//!      constexpr auto asec[raw](floating_value auto x)                     noexcept; // 2
//!      constexpr auto asec[rad](floating_value auto x)                     noexcept; // 1
//!      constexpr auto asec[deg](floating_value auto x)                     noexcept; // 3
//!      constexpr auto asec[pirad](floating_value auto x)                   noexcept; // 4
///!
//!      // Lanes masking
//!      constexpr auto asec[conditional_expr auto c](floating_value auto x) noexcept; // 5
//!      constexpr auto asec[logical_value auto m](floating_value auto x)    noexcept; // 5
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!    * `x`: [floating value](@ref eve::floating_value).
//!    * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!    * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//! **Return value**
//!
//!    1. Returns the [elementwise](@ref glossary_elementwise) arc cosecant of the
//!      input in the range \f$[0 , \pi]\f$.
//!      In particular:
//!      * If the element is \f$1\f$, \f$+0\f$ is returned.
//!      * If the element is \f$0\f$, \f$\pi\f$ is returned.
//!      * If the element \f$|x| < 1\f$, `NaN` is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!    2. Same as 1 but uses a faster implementation which can be slightly less accurate near 'x = 1'
//!    1. Result in degrees
//!    2. Result in \f$\pi\f$ multiples
//!    3. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Inverse Cosecant](https://mathworld.wolfram.com/InverseCosecant.html)
//!   *  [Wikipedia: Inverse trigonometricfunctions](https://en.wikipedia.org/wiki/Inverse_trigonometric_functions)
//!   *  [DLMF](https://dlmf.nist.gov/4.23)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/asec.cpp}
//================================================================================================
  inline constexpr auto asec = functor<asec_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T asec_(EVE_REQUIRES(cpu_), O const& o, T const& a)
    {
      return eve::acos[o](rec[pedantic](a));
    }
  }
  constexpr auto asecd = eve::asec[eve::deg];
  constexpr auto asecpi= eve::asec[eve::radpi];
}
