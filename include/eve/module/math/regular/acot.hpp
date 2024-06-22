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
  struct acot_t : elementwise_callable<acot_t, Options>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(acot_t, acot_);
};

//======================================================================================================================
//! @addtogroup math_invtrig
//! @{
//!   @var acot
//!   @brief `elementwise_callable` object computing the arc cotangent.
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
//!      constexpr auto acot(floating_value auto x)                         noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto acot[conditional_expr auto c](floatingvalue auto x) noexcept; // 2.1
//!      constexpr auto acot[logical_value auto m](floatingvalue auto x)    noexcept; // 2.2
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
//!    1. Returns the [elementwise](@ref glossary_elementwise) arc cotangent of the
//!      input in the range  \f$[-\frac\pi2, \frac\pi2]\f$.
//!      In particular:
//!       * If the element is \f$\pm0\f$, \f$\pm\frac\pi2\f$ is returned.
//!       * If the element is \f$\pm\infty\f$, \f$\pm0\f$ is returned.
//!       * If the element is a `Nan`, `NaN` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/regular/acot.cpp}
//!  @}
//======================================================================================================================
  inline constexpr auto acot = functor<acot_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T acot_(EVE_REQUIRES(cpu_), O const&, T const& a)
    {
      if constexpr( has_native_abi_v<T> )
      {
        auto x = eve::abs(a);
        return bit_xor(atan_kernel(rec[pedantic2](x), x), bitofsign(a));
      }
      else
        return apply_over(acot, a);
    }
  }
}
