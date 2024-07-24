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

namespace eve
{
  template<typename Options>
  struct acotd_t : elementwise_callable<acotd_t, Options>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(acotd_t, acotd_);
};

//================================================================================================
//! @addtogroup math_invtrig
//! @{
//!   @var acotd
//!   @brief  `elementwise_callable` object computing the arc cotangent in degree.
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
//!      constexpr auto acotd(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto acotd[conditional_expr auto c](floating_value auto x) noexcept; // 2.1
//!      constexpr auto acotd[logical_value auto m](floating_value auto x)    noexcept; // 2.2
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
//!    1. Returns the [elementwise](@ref glossary_elementwise) value in degrees of the arc cotangent of the
//!      input in the range \f$[-90 , 90]\f$.
//!      In particular:
//!      * If the element is \f$\pm0\f$, \f$\pm90\f$ is returned.
//!      * If the element is \f$\pm\infty\f$, \f$\pm0\f$ is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math//acotd.cpp}
//!  @}
//================================================================================================
  inline constexpr auto acotd = functor<acotd_t>;
//================================================================================================
//================================================================================================


  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T acotd_(EVE_REQUIRES(cpu_), O const&, T const& a)
    {
      return radindeg(acot(a));
    }
  }
}
