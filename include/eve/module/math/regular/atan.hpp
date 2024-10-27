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
#include <eve/module/math/detail/generic/atan_kernel.hpp>

namespace eve
{
  template<typename Options>
  struct atan_t : elementwise_callable<atan_t, Options>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(atan_t, atan_);
  };


//================================================================================================
//! @addtogroup math_invtrig
//! @{
//!   @var atan
//!   @brief `elementwise_callable` object computing the arc tangent.
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
//!      constexpr auto atan(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto atan[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto atan[logical_value auto m](floating_value auto x)    noexcept; // 2
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
//!    1. Returns the [elementwise](@ref glossary_elementwise) arc tangent of the
//!      input in the range  \f$[-\frac\pi2, \frac\pi2]\f$.
//!      In particular:
//!      * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!      * If the element is \f$\pm\infty\f$, \f$\pm\frac\pi2\f$ is returned.
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
//!  @godbolt{doc/math/atan.cpp}
//================================================================================================
 inline constexpr auto atan = functor<atan_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T atan_(EVE_REQUIRES(cpu_), O const& , T const& a)
    {
      T x = eve::abs(a);
      return bit_xor(atan_kernel(x, rec[pedantic](x)), bitofsign(a));
    }
  }
}
