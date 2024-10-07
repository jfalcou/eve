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
#include <eve/module/core/regular/signnz.hpp>


namespace eve
{
  template<typename Options>
  struct negatenz_t : elementwise_callable<negatenz_t, Options>
  {
    template<value T, value U>
    constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T a, U b) const
      requires (eve::same_lanes_or_scalar<T, U>)
    {
      return EVE_DISPATCH_CALL_PT((common_value_t<T, U>), a, b);
    }

    EVE_CALLABLE_OBJECT(negatenz_t, negatenz_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var negatenz
//!   @brief `elementwise_callable` object computing the product of the first parameter
//!   by the never zero sign of the second.
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
//!      constexpr auto negatenz(value auto x, value auto y)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto negatenz[conditional_expr auto c](value auto x, value auto y) noexcept; // 2
//!      constexpr auto negatenz[logical_value auto m](value auto , value auto yx)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [arguments](@ref eve::value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!      1. The [elementwise](@ref glossary_elementwise) product of the first parameter
//!         by the never zero sign of the second is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/negatenz.cpp}
//================================================================================================
  inline constexpr auto negatenz = functor<negatenz_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    EVE_FORCEINLINE constexpr T
    negatenz_(EVE_REQUIRES(cpu_), O const &o, T const &a, T const &b) noexcept
    {
      if constexpr( signed_value<T> )
        return a * signnz[o](b);
      else
        return a;
    }
  }
}
