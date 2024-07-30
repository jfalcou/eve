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
#include <eve/module/math/regular/asin.hpp>
#include <eve/module/math/regular/radindeg.hpp>

namespace eve
{
  template<typename Options>
  struct asind_t : elementwise_callable<asind_t, Options, raw_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(asind_t, asind_);
  };


//================================================================================================
//! @addtogroup math_invtrig
//! @{
//!   @var asind
//!   @brief  `elementwise_callable` object computing the arc sine in degree.
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
//!      constexpr auto asind(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto asind[conditional_expr auto c](floating_value auto x) noexcept; // 2.1
//!      constexpr auto asind[logical_value auto m](floating_value auto x)    noexcept; // 2.2
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
//!    1. Returns the [elementwise](@ref glossary_elementwise) value in degrees of the arc sine of the
//!      input in the range \f$[-90 , 90]\f$.
//!      In particular:
//!      * If the element is \f$\pm0\f$, it is returned unmodified.
//!      * If the element \f$|x| > 1\f$, `NaN` is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/asind.cpp}
//================================================================================================
  inline constexpr auto asind = functor<asind_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T asind_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      return radindeg(asin(a0));
    }
  }
}
