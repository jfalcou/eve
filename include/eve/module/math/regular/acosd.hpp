//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/math/regular/acos.hpp>
#include <eve/module/math/regular/radindeg.hpp>

namespace eve
{
  template<typename Options>
  struct acosd_t : elementwise_callable<acosd_t, Options, raw_option>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(acosd_t, acosd_);
  };
  
//================================================================================================
//! @addtogroup math_invtrig
//! @{
//!   @var acosd
//!   @brief  `elementwise_callable` object computing the arc cosine in degree.
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
//!      constexpr auto acosd(floating_value auto x)      noexcept; // 1
//!      constexpr auto acosd[raw](floating_value auto x) noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto acosd[conditional_expr auto c](value auto x) noexcept;  // 3.1
//!      constexpr auto acosd[logical_value auto m](value auto x)    noexcept;  // 3.2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [floating value](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) maskin. The operation.
//!     * `m`: [Logical value](logical) maskin. The operation.
//!
//! **Return value**
//!
//!    1. Returns the [elementwise](@ref glossary_elementwise) value in degrees of the arc cosine of the
//!      input in the range \f$[0 , 180]\f$.
//!      In particular:
//!      * If `x` is \f$1\f$, \f$+0\f$ is returned.
//!      * If \f$|x| > 1\f$, `NaN` is returned.
//!      * If `x` is a `NaN`, `NaN` is returned.
//!    2. Same as 1 but uses a faster implementation which can be slightly less accurate near 'x = 1'
//!    3. [The operation is performed conditionnaly.](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/regular/acosd.cpp}
//!  @}
//================================================================================================
  inline constexpr auto acosd = functor<acosd_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T acosd_(EVE_REQUIRES(cpu_), O const& o, T const& a0)
    {
      return radindeg(acos[o](a0));
    }
  }
}
