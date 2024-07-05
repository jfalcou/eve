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
  struct negate_t : elementwise_callable<negate_t, Options>
  {
    template<value T,  value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T a, U b) const
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(negate_t, negate_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var negate
//!   @brief `elementwise_callable` object computing the product of the first parameter
//!   by the sign of the second.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto negate(value auto x, value auto y)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto negate[conditional_expr auto c](value auto x, value auto y) noexcept; // 2
//!      constexpr auto negate[logical_value auto m](value auto , value auto yx)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [arguments](@ref eve::value).
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!      1. The [elementwise](@ref glossary_elementwise) product of the first parameter
//!         by the sign of the second is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/negate.cpp}
//! @}
//================================================================================================
 inline constexpr auto negate = functor<negate_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto
    negate_(EVE_REQUIRES(cpu_), O const &, T const &a,  T const &b) noexcept
    {
      if constexpr( signed_value<T> )
        return a * sign(b);
      else
        return if_else(is_nez(b), a, eve::zero);
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/negate.hpp>
#endif
