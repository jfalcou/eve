/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/function/to_logical.hpp>
#include <eve/function/is_not_equal.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup comparisons
  //! @{
  //! @var is_nez
  //!
  //! @brief Callable object computing the "not equal to zero" predicate.
  //!
  //! **Required header:** `#include <eve/function/is_nez.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the "not equal to zero" predicate   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T > auto operator()( T x ) const noexcept
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [values](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!Returns the logical value containing the [elementwise](@ref glossary_elementwise) inequality test result
  //!between `x` and 0.
  //!
  //!The result type is `logical< T >`.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::is_nez
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `is_nez[cond](x)` is equivalent to
  //! `if_else(cond,is_nez(x),false(as(is_nez(x))))`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/is_nez.cpp}
  //!
  //!  @}
  //================================================================================================

  EVE_MAKE_CALLABLE(is_nez_, is_nez);
}

namespace eve::detail
{
  template<value T>
  EVE_FORCEINLINE constexpr auto is_nez_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    return detail::to_logical(a);
  }


  // -----------------------------------------------------------------------------------------------
  // logical masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto is_nez_(EVE_SUPPORTS(cpu_), C const &cond, U const &u) noexcept
  {
    return is_not_equal[cond](u, zero(as(u)));
  }
}
