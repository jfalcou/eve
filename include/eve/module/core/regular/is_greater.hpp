//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/detail/tolerance.hpp>
#include <eve/module/core/regular/is_less.hpp>

namespace eve
{
  template<typename Options>
  struct is_greater_t : elementwise_callable<is_greater_t, Options, definitely_option>
  {
    template<arithmetic_value T, arithmetic_value U>
    constexpr EVE_FORCEINLINE common_logical_t<T, U> operator()(T a, U b) const
      requires (compatible_arithmetic_values<T, U>)
    {
      if constexpr (Options::contains(definitely))
      {
        static_assert(floating_value<T>, "[eve::is_greater] The definitely option is only supported for floating types.");
        // static_assert( valid_tolerance<common_value_t<T, U>, Options>::value, "[eve::is_greater] simd tolerance requires at least one simd parameter." );
      }

      return is_less[this->options()](b, a);
    }

    EVE_CALLABLE_OBJECT(is_greater_t, is_greater_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_greater
//!   @brief `elementwise callable` returning a logical true  if and only if the element value of the first parameter is
//!          greater  than the second one.
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
//!      constexpr auto is_greater(value auto x, value auto y) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto is_greater[conditional_expr auto c](value auto x, value auto y) noexcept; // 2
//!      constexpr auto is_greater[logical_value auto m](value auto x, value auto y) noexcept;    // 2
//!
//!      // Semantic option
//!      constexpr auto is_greater[definitely](/*any of the above overloads*/)          noexcept; // 3
//!      constexpr auto is_greater[definitely = tol](/*any of the above overloads*/)    noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [arguments](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!     * `tol`: [scalar value](@ref eve::value) tolerance.
//!
//!   **Return value**
//!
//!     1. The call `eve::is_greater(x,y)`  is semantically  equivalent to `x > y`:
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!     3. The expression `is_greater[definitely = tol](x, y)` where `x` and `y` must be
//!         floating point values, evaluates to true if and only if `x` is definitely greater than `y`.
//!         This means that:
//!            - if `tol` is a floating value then  \f$x > y + \mbox{tol}\cdot \max(|x|, |y|)\f$
//!            - if `tol` is a positive integral value then \f$x > \mbox{next}(y, \mbox{tol})\f$;
//!            - if `tol` is omitted then the tolerance `tol` default to `3*eps(as(x))`.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_greater.cpp}
//================================================================================================
  inline constexpr auto is_greater = functor<is_greater_t>;
//================================================================================================
//! @}
//================================================================================================
}
