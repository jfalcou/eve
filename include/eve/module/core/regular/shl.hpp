//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/assert.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/detail/overload.hpp>

#include <type_traits>

namespace eve
{
//================================================================================================
//! @addtogroup core
//! @{
//! @var shl
//!
//! @brief Callable object computing the arithmetic left shift operation.
//!
//! **Required header:** `#include <eve/module/core.hpp>`
//!
//! #### Members Functions
//!
//! | Member       | Effect                                                     |
//! |:-------------|:-----------------------------------------------------------|
//! | `operator()` | the arithmetic left shift operation   |
//! | `operator[]` | Construct a conditional version of current function object |
//!
//! ---
//!
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
//!  template< value T, integral_value U > auto operator()( T x, U n ) const noexcept
//!   requires bit_compatible< T, U >;
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//!
//! **Parameters**
//!
//!`x`:   [value](@ref eve::value).
//!
//!`n`:   [integral value](@ref eve::value).
//!
//! **Return value**
//!
//! Computes the [elementwise](@ref glossary_elementwise) arithmetic left shift of the first
//! parameter by the second one.
//!
//! the call `shl(x, n)` is equivalent to `x << n` if `x`  is an  [simd value](@ref
//! eve::simd_value).
//!
//! The types must share the same cardinal or be scalar and if `N` is the size in bits  of the
//! element type of `T`, all  [elements](@ref glossary_elementwise) of n must belong to the
//! interval: `[0, N[` or the result is undefined.
//!
//!  @warning
//!     Although the infix notation with `<<` is supported, the `<<` operator on
//!     standard scalar types is the original one and so can not be overloaded on standard floating
//!     parameters due to **C++** limitations.
//!
//! ---
//!
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
//!  auto operator[]( conditional_expression auto cond ) const noexcept;
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//!
//!  Higher-order function generating a masked version of eve::shl
//!
//!  **Parameters**
//!
//!  `cond` : conditional expression
//!
//!  **Return value**
//!
//!  A Callable object so that the expression `shl[cond](x, ...)` is equivalent to
//!  `if_else(cond,shl(x, ...),x)`
//!
//! ---
//!
//! #### Supported decorators
//!
//!  no decorators are supported
//!
//! #### Example
//!
//! @godbolt{doc/core/shl.cpp}
//!
//!  @}
//================================================================================================
namespace tag
{
  struct shl_;
}

namespace detail
{
  template<typename T, typename S>
  EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::shl_), T const&, [[maybe_unused]] S const& s)
  {
    EVE_ASSERT(assert_good_shift<T>(s),
               "[eve::shl] Shifting by " << s << " is out of the range [0, "
                                         << sizeof(element_type_t<T>) * 8 << "[.");
  }
}

EVE_MAKE_CALLABLE(shl_, shl);
}

#include <eve/module/core/regular/impl/shl.hpp>
