//================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/math/regular/acos.hpp>
#include <eve/module/math/regular/radindeg.hpp>

namespace eve
{
template<typename Options>
struct asecd_t : elementwise_callable<asecd_t, Options, raw_option>
{
  template<eve::floating_value T>
  constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(asecd_t, asecd_);
};
//================================================================================================
//! @addtogroup math_invtrig
//! @{
//!   @var asecd
//!   @brief  `elementwise_callable` object computing the arc secant in degree.
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
//!      // Regular overloads
//!      constexpr auto asecd(floating_value auto x)                          noexcept; // 1
//!
//!      // Semantic option
//!      constexpr auto asecd[raw](floating_value auto x)                     noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto asecd[conditional_expr auto c](floating_value auto x) noexcept; // 3
//!      constexpr auto asecd[logical_value auto m](floating_value auto x)    noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [floating value](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//! **Return value**
//!
//!    1. Returns the [elementwise](@ref glossary_elementwise) value in degrees of the arc secant of the
//!      input in the range \f$[0 , 180]\f$.
//!      In particular:
//!      * If the element is \f$1\f$, \f$+0\f$ is returned.
//!      * If the element is \f$0\f$, \f$180\f$ is returned.
//!      * If the element \f$|x| < 1\f$, `NaN` is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!    2. Same as 1 but uses a faster implementation which can be slightly less accurate near 'x = 1'
//!    3. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/asecd.cpp}
//================================================================================================
  inline constexpr auto asecd = functor<asecd_t>;
//================================================================================================
//!  @}
//================================================================================================


namespace detail
{
  template<typename T, callable_options O>
  constexpr EVE_FORCEINLINE T asecd_(EVE_REQUIRES(cpu_), O const& o, T const& a)
  {
    return radindeg(asec[o](a));
  }
}
}
