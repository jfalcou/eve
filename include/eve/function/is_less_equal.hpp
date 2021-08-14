//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <eve/detail/implementation.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup comparisons
  //! @{
  //! @var is_less_equal
  //!
  //! @brief Callable object computing the "less or equal to" predicate.
  //!
  //! **Required header:** `#include <eve/function/is_less_equal.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the "less or equal to" predicate   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::is_less_equal
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `is_less_equal[cond](x, y)` is equivalent to
  //! `if_else(cond,is_less_equal(x, y),false(as(is_less_equal(x, y)))`
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U > auto operator()( T x, U y ) const noexcept requires compatible< T, U >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [values](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!Returns the logical value containing the [element-wise](@ref glossary_elementwise)
  //! comparison test result between `x` and `y`. The infix notation `x <= y` can also be used.
  //!
  //!The result type is the [compatibility result](../../concept.html#compatibility) of the two parameters.
  //!
  //!@warning
  //!   Although the infix notation with `<=` is supported, the `<=` operator on
  //!   standard scalar types is the original one and so returns bool result, not `logical`.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::is_less_equal
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `is_less_equal[cond](x, y)` is equivalent to
  //! `if_else(cond,is_less_equal(x, y),false(as(is_less_equal(x, y))))`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/is_less_equal.cpp
  //!
  //!  @}
  //================================================================================================

  EVE_MAKE_CALLABLE(is_less_equal_, is_less_equal);

  namespace detail
  {
    template<value T, value U>
    EVE_FORCEINLINE auto is_less_equal_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
    {
      if constexpr( scalar_value<T> && scalar_value<U> )  return as_logical_t<T>(a <= b);
      else                                                return a <= b;
    }

    // -----------------------------------------------------------------------------------------------
    // logical masked case
    template<conditional_expr C, real_value U, real_value V>
    EVE_FORCEINLINE auto is_less_equal_(EVE_SUPPORTS(cpu_), C const &cond, U const &u, V const &v) noexcept
    {
      return logical_mask_op(cond, is_less_equal, u, v);
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/is_less_equal.hpp>
#endif
