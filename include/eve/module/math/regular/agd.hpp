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
#include <eve/module/math/regular/tan.hpp>
#include <eve/module/math/regular/atan.hpp>

namespace eve
{
  template<typename Options>
  struct agd_t : elementwise_callable<agd_t, Options>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(agd_t, agd_);
};

//================================================================================================
//! @addtogroup math_invhyper
//! @{
//!   @var agd
//!   @brief `elementwise_callable` object computing the inverse gudermanian,
//!   i.e. \f$2\tanh(\tan(x/2))\f$.
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
//!      constexpr auto agd(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto agd[conditional_expr auto c](floating_value auto x) noexcept; // 2.1
//!      constexpr auto agd[logical_value auto m](floating_value auto x)    noexcept; // 2.2
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
//!    1. Returns the [elementwise](@ref glossary_elementwise) inverse
//!      [gudermanian](@ref eve::gd) of the input.
//!      In particular:
//!      * If the element is \f$\pm0\f$, \f$0\f$ is returned.
//!      * If the element is \f$\pm\pi/2\f$, \f$\infty\f$ is returned.
//!      * If the element is not in \f$[-\pi/2, \pi/2] \f$, `NaN` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/InverseGudermannian.html)
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Gudermannian_function)
//!   *  [DLMF](https://dlmf.nist.gov/4.23#viii)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/agd.cpp}
//================================================================================================
  inline constexpr auto agd = functor<agd_t>;
//================================================================================================
//!  @}
//======================================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T agd_(EVE_REQUIRES(cpu_), O const&, T const& x)
    {
      return 2*atanh(tan(x*half(as(x))));
    }
  }
}
