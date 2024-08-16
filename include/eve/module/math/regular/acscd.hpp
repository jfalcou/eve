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
#include <eve/module/math/regular/radindeg.hpp>
#include <eve/module/math/regular/acsc.hpp>

namespace eve
{
  template<typename Options>
  struct acscd_t : elementwise_callable<acscd_t, Options>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(acscd_t, acscd_);
};

//================================================================================================
//! @addtogroup math_invtrig
//! @{
//!   @var acscd
//!   @brief `elementwise_callable` object computing the arc cosecant.
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
//!      constexpr auto acscd(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto acscd[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto acscd[logical_value auto m](floating_value auto x)    noexcept; // 2
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
//!    1. Returns the [elementwise](@ref glossary_elementwise) arc cosecant of the
//!      input in the range \f$[-90, 90]\f$.
//!      In particular:
//!      * If the element is \f$\pm1\f$, \f$\pm90\f$ is returned.
//!      * If the element \f$|x| < 1\f$, `NaN` is returned.
//!      * If the element is \f$\pm\infty\f$, \f$\pm0\f$ is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Inverse Cosecant](https://mathworld.wolfram.com/InverseCosecant.html)
//!   *  [Wikipedia: Inverse trigonometricfunctions](https://en.wikipedia.org/wiki/Inverse_trigonometric_functions)
//!   *  [DLMF](https://dlmf.nist.gov/4.23)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/acscd.cpp}
//================================================================================================
  inline constexpr auto acscd = functor<acscd_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T acscd_(EVE_REQUIRES(cpu_), O const&, T const& a)
    {
      return radindeg(acsc(a));
    }
  }
}
