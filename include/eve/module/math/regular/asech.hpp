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
#include <eve/module/math/acosh.hpp>

namespace eve
{
  template<typename Options>
  struct asech_t : elementwise_callable<asech_t, Options>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(asech_t, asech_);
};


//================================================================================================
//! @addtogroup math_invhyper
//! @{
//!   @var asech
//!   @brief `elementwise_callable` object computing the inverse hyperbolic secant: \f$\log(1/x+\sqrt{1/x^2-1})\f$.
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
//!      constexpr auto asech(floating_value auto x)                         noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto asech[conditional_expr auto c](floating_value auto x) noexcept; // 2.1
//!      constexpr auto asech[logical_value auto m](floating_value auto x)    noexcept; // 2.2
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
//!    1. Returns the [elementwise](@ref glossary_elementwise) inverse hyperbolic secant of the
//!      input in the range  \f$[-\frac\pi2, \frac\pi2]\f$.
//!      In particular:
//!       * If the element is \f$\pm0\f$, \f$\pm\infty\f$ is returned.
//!       * If the element is \f$1\f$, \f$+0\f$ returned.
//!       * If the element does not belong to \f$[0,1]\f$, `NaN` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/asech.cpp}
//!  @}
//======================================================================================================================
  inline constexpr auto asech = functor<asech_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T asech_(EVE_REQUIRES(cpu_), O const&, T const& x)
    {
      return acosh(rec[pedantic2](x));
    }
  }
}
