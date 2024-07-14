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
  struct rem_t : elementwise_callable<rem_t, Options, upward_option, downward_option,
                                      to_nearest_option, toward_zero_option>
  {
    template<eve::value T0, value T1>
    requires(eve::same_lanes_or_scalar<T0, T1>)
    EVE_FORCEINLINE constexpr common_value_t<T0, T1> operator()(T0 t0, T1 t1) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1);
    }

    EVE_CALLABLE_OBJECT(rem_t, rem_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var rem
//!   @brief `elementwise_callable` object computing the  remainder after division.
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
//!      constexpr auto rem(floating_value auto x, index_t<scale>)       noexcept; // 1
//!      constexpr auto rem(floating_value auto x, int scale)            noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto rem[conditional_expr auto c](value auto x)       noexcept; // 2
//!      constexpr auto rem[logical_value auto m](value auto x)          noexcept; // 2
//!
//!      // Semantic option
//!      constexpr auto rem[downward](/*any of the above overloads*/)    noexcept; // 3
//!      constexpr auto rem[upward](/*any of the above overloads*/)      noexcept; // 3
//!      constexpr auto rem[to_nearest](/*any of the above overloads*/)  noexcept; // 3
//!      constexpr auto rem[toward_zero](/*any of the above overloads*/) noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`: [values](@ref value) argumentx.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!      1. Return the remainder after division of `x` by `y` and is
//!         equivalent to  `x-div[toward_zero](x, y)*y`.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!      3. The call is equivalent to  `x-div[o](x, y)*y` where `o` is the chosen option.
//!         For unsigned integral the options upward and nearest are undefined behaviour as the result could
//!         be negative.
//!
//!    @notes Although the infix notation with `%` is supported, the `%` operator on
//!     standard integral scalar type is the original one and so can lead to automatic
//!     promotion. Moreover due to C++ limitations, `%` is not available for scalar floating
//!     point values.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/rem.cpp}
//! @}
//================================================================================================
  inline constexpr auto rem = functor<rem_t>;
}

#include <eve/module/core/regular/impl/rem.hpp>
