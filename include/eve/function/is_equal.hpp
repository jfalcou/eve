//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/function/friends.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup comparisons
  //! @{
  //! @var is_equal
  //!
  //! @brief Callable object computing the equality predicate.
  //!
  //! **Required header:** `#include <eve/function/is_equal.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the equality predicate   |
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
  //!`x`, `y`:   [values](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!Returns the logical value containing the [element-wise](../../../glossary.html#value) equality test result
  //!between `x` and `y`. The infix notation `x == y` can also be used.
  //!
  //!The result type is the [compatibility result](../../concept.html#compatibility) of the two parameters.
  //!
  //!@warning
  //!   Although the infix notation with `==` is supported, the `==` operator on
  //!   standard scalar types is the original one and so returns bool result, not `logical`.
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::is_less
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `is_equal[cond](x, y)` is equivalent to
  //! `if_else(cond,is_equal(x, y),false(as(is_equal(x, y))))`
  //!
  //! ---  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * `numeric`
  //!
  //!     **Required header:**  #include <eve/function/numeric/is_equal.hpp>
  //!
  //!     The expression `numeric(is_equal)(x,y)` considers that Nan values are equal.
  //!
  //!  * `almost`
  //!
  //!     **Required header:**  #include <eve/function/fuzzy/is_equal.hpp>
  //!
  //!     The expression `almost(is_equal)(x, y, t)` where `x` and `y` must be floating point values, evals to
  //!      true if and only if `x` is almost equal to `y`.
  //!      This means that:
  //!
  //!      - if `t` is a floating_value then the relative error of confusing is `x` and `y` is less than `t` \f$(|x-y| \le t \max(|x|, |y|))\f$.
  //!      - if `t` is a positive integral_value then there are not more than `t` values of the type of `x` representable in the interval \f$[x,y[\f$.
  //!      - if `t` is omitted then the tolerance `t` is taken to 3 times the machine \f$\epsilon\f$ in the `x` type (`3*eps(as(x))`).
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/is_equal.cpp
  //!
  //!  @}
  //================================================================================================

  EVE_IMPLEMENT_CALLABLE(is_equal_, is_equal);

  namespace detail
  {
    template<value T, value U>
    EVE_FORCEINLINE auto is_equal_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
    {
      if constexpr( scalar_value<T> && scalar_value<U> )  return as_logical_t<T>(a == b);
      else                                                return a == b;
    }

    // -----------------------------------------------------------------------------------------------
    // logical masked case
    template<conditional_expr C, real_value U, real_value V>
    EVE_FORCEINLINE auto is_equal_(EVE_SUPPORTS(cpu_), C const &cond, U const &u, V const &v) noexcept
    {
      return lmask_op(cond, is_equal, u, v);
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/is_equal.hpp>
#endif
