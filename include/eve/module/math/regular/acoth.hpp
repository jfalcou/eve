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
#include <eve/module/math/regular/atanh.hpp>

namespace eve
{
  template<typename Options>
  struct acoth_t : elementwise_callable<acoth_t, Options>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(acoth_t, acoth_);
};

//================================================================================================
//! @addtogroup math_invhyper
//! @{
//!   @var acoth
//!   @brief `elementwise_callable` object computing the inverse hyperbolic cotangent.
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
//!      constexpr auto acoth(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto acoth[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto acoth[logical_value auto m](floating_value auto x)    noexcept; // 2
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
//!    1. Returns the [elementwise](@ref glossary_elementwise) inverse hyperbolic cotangent of the
//!      input in the range  \f$[-\frac\pi2, \frac\pi2]\f$.
//!      In particular:
//!      * If the element is \f$\pm1\f$, \f$\pm0\f$ is returned.
//!      * If the element is \f$\pm\infty\f$, \f$\pm1\f$ is returned.
//!      * If the element is less than one or a `NaN`, `NaN` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Inverse Hyperbolic Cotangent](https://mathworld.wolfram.com/InverseHyperbolicCotangent.html)
//!   *  [Wikipedia: Inverse hyperbolic functions](https://en.wikipedia.org/wiki/Inverse_hyperbolic_functions)
//!   *  [DLMF](https://dlmf.nist.gov/4.37)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/acoth.cpp}
//================================================================================================
  inline constexpr auto acoth = functor<acoth_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T acoth_(EVE_REQUIRES(cpu_), O const&, T const& x)
    {
      return eve::atanh(rec[pedantic](x));
    }
  }
}
