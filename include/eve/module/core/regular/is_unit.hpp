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
#include <eve/module/core/regular/sqr.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_unit_t : elementwise_callable<is_unit_t, Options, pedantic_option>
  {
    template<value T>
    EVE_FORCEINLINE constexpr as_logical_t<T> operator()(T t) const noexcept
    {
      return this->behavior(as<as_logical_t<T>>{}, eve::current_api, this->options(), t);
    }

    EVE_CALLABLE_OBJECT(is_unit_t, is_unit_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_unit
//!   @brief `elementwise callable` returning a logical true  if and only if the element value is zero.
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
//!      constexpr auto is_unit(value auto x) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto is_unit[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto is_unit[logical_value auto m](value auto x) noexcept;    // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1. The call `is_unit(x)` is semantically  equivalent to  `abs(x) == 1`
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_unit.cpp}
//================================================================================================
  inline constexpr auto is_unit = functor<is_unit_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    EVE_FORCEINLINE as_logical_t<T>
    is_unit_(EVE_REQUIRES(cpu_), O const&, T const& a) noexcept
    {
      return is_equal(abs(a), one(as<T>{}));
    }
  }
}
