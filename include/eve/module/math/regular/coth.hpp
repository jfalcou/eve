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
#include <eve/module/math/regular/expm1.hpp>

namespace eve
{
  template<typename Options>
  struct coth_t : elementwise_callable<coth_t, Options>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(coth_t, coth_);
  };

//================================================================================================
//! @addtogroup math_hyper
//! @{
//! @var coth
//! @brief `elementwise_callable` object computing the hyperbolic cotangent: \f$\frac{e^x+e^{-x}}{e^x-e^{-x}}\f$.
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
//!      constexpr auto coth(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto coth[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto coth[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!     * `x`: [floating value](@ref floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//! **Return value**
//!
//!   1.  Returns the [elementwise](@ref glossary_elementwise) hyperbolic cotangent of the input.
//!       In particular:
//!        * If the element is \f$\pm0\f$, \f$\pm\infty\f$ is returned.
//!        * If the element is \f$\pm\infty\f$, \f$\pm1\f$ is returned.
//!        * If the element is a `NaN`, `NaN` is returned.
//!   2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/coth.cpp}
//================================================================================================
  inline constexpr auto coth = functor<coth_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T coth_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      auto x = eve::abs(a0 + a0);
      auto t = rec[pedantic](expm1(x));
      auto r = fma(T(2), t, T(1));
      return copysign(r, a0);
    }
  }
}
