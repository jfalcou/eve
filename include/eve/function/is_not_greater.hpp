//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup comparisons
  //! @{
  //! @var is_not_greater
  //!
  //! @brief Callable object performing the computation of the "not greater than" predicate.
  //!
  //! **Required header:** `#include <eve/function/is_not_greater.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the "not greater than" predicate   |
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
  //!Returns the logical value containing the [element-wise](../../../glossary.html#value) comparison test result
  //!between `x` and `y`.
  //!
  //!The result type is the [compatibility result](../../concept.html#compatibility) of the two parameters.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::is_not_greater
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `is_not_greater[cond](x, ...)` is equivalent to `if_else(cond,is_not_greater(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  ====================================================================================================
  //!  * `almost`
  //!
  //!     **Required header:**  #include <eve/function/almost/is_not_greater.hpp>
  //! 
  //!  
  //!     The expression `almost(is_not_greater)(x, y, t)` where `x` and `y` must be
  //!      floating point values, evals to true if and only if and only if `x` is not almost greater than `y`.
  //!      This means that:
  //!  
  //!      - if `t` is a floating_value then  \f$(x < y + t \max(|x|, |y|))\f$
  //!      - if `t` is a positive integral_value then \f$(x < \mbox{next}(y, t)\f$;
  //!      - if `t` is omitted then the tolerance `t` default to `3*eps(as(x))`.
  //!  
  //!  The result type is the [compatibility result](../../concept.html#compatibility) of the two parameters.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/is_not_greater.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(is_not_greater_, is_not_greater);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/is_not_greater.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/is_not_greater.hpp>
#endif
