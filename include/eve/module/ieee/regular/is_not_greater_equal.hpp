//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup comparisons
  //! @{
  //! @var is_not_greater_equal
  //!
  //! @brief Callable object computing the "not greater or equal to" predicate.
  //!
  //! **Required header:** `#include <eve/function/is_not_greater_equal.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the "not greater or equal to" predicate   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U > auto operator()( T x, U y ) const noexcept requires compatible< T, U >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [values](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!Returns the logical value containing the [elementwise](@ref glossary_elementwise) comparison test result
  //!between `x` and `y`.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::is_not_greater_equal
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `is_not_greater_equal[cond](x, y)` is equivalent to
  //! `if_else(cond,is_not_greater_equal(x, y),false(as(is_not_greater_equal(x, y))))`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * `definitely`
  //!
  //!     **Required header:** `#include <eve/function/fuzzy/is_not_greater_equal.hpp>`
  //!
  //!     The expression `definitely(is_not_greater_equal)(x, y, t)` where `x` and `y` must be
  //!      floating point values, evals to true if and only if and only if `x` is definitely not greater or equal to `y`.
  //!      This means that the pair `x, y` is unordered or:
  //!
  //!      - if `t` is a floating_value then  \f$(x \le y - t \max(|x|, |y|))\f$
  //!      - if `t` is a positive integral_value then \f$(x \le \mbox{prev}(y, t)\f$;
  //!      - if `t` is omitted then the tolerance `t` default to `3*eps(as(x))`.
  //!
  //!  The result type is the [common compatible type](@ref common_compatible) of the two parameters.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/is_not_greater_equal.cpp}
  //!
  //!  @}
  //================================================================================================

  EVE_MAKE_CALLABLE(is_not_greater_equal_, is_not_greater_equal);
}

#include <eve/arch.hpp>
#include <eve/module/ieee/regular/impl/is_not_greater_equal.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/ieee/regular/impl/simd/x86/is_not_greater_equal.hpp>
#endif
