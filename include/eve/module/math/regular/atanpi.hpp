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
#include <eve/module/math/regular/atan.hpp>
#include <eve/module/math/regular/radindeg.hpp>

namespace eve
{
  template<typename Options>
  struct atanpi_t : elementwise_callable<atanpi_t, Options>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(atanpi_t, atanpi_);
  };

//================================================================================================
//! @addtogroup math_invtrig
//! @{
//!   @var atanpi
//!   @brief Callable object computing te arc tangent in \f$\pi\f$ multiples.
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
//!      constexpr auto atanpi(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto atanpi[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto atanpi[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [floating value](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//! **Return value**
//!
//!    1. Returns the [elementwise](@ref glossary_elementwise) value in \f$\pi\f$ multiples
//!      of the arc tangent of the input in the range \f$]-\frac12, \frac12]\f$.
//!      In particular:
//!      * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!      * If the element is \f$\pm\infty\f$, \f$\pm\frac12\f$ is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: atan](https://en.cppreference.com/w/cpp/numeric/math/atan)
//!   *  [Wolfram MathWorld: Inverse Tangent](https://mathworld.wolfram.com/InverseTangent.html)
//!   *  [Wikipedia: Inverse trigonometric functions](https://en.wikipedia.org/wiki/Inverse_trigonometric_functions)
//!   *  [DLMF: Inverse trigonometric functions](https://dlmf.nist.gov/4.23)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/atanpi.cpp}
//================================================================================================
 inline constexpr auto atanpi = functor<atanpi_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T atanpi_(EVE_REQUIRES(cpu_), O const& , T const& a)
    {
      return radinpi(atan(a));
    }
  }
}
