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
  //! @var is_less
  //!
  //! @brief Callable object computing the "less than" predicate.
  //!
  //! **Required header:** `#include <eve/function/is_less.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the "less than" predicate   |
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
  //!between `x` and `y`. The infix notation `x < y` can also be used.
  //!
  //!The result type is the [compatibility result](../../concept.html#compatibility) of the two parameters.
  //!
  //!@warning
  //!   Although the infix notation with `<` is supported, the `<` operator on
  //!   standard scalar types is the original one and so returns bool result, not `logical`.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * `definitely`
  //!
  //!     **Required header:**  #include <eve/function/fuzzy/is_less.hpp>
  //!  
  //!     The expression `definitely(is_less)(x, y, t)` where `x` and `y` must be
  //!      floating point values, evals to true if and only if and only if `x` is definitely less than `y`.
  //!      This means that:
  //!  
  //!      - if `t` is a floating_value then  \f$(x < y - t \max(|x|, |y|))\f$
  //!      - if `t` is a positive integral_value then \f$(x < \mbox{prev}(y, t)\f$;
  //!      - if `t` is omitted then the tolerance `t` default to `3*eps(as(x))`.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/is_less.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(is_less_, is_less);

  namespace detail
  {
    template<value T, value U>
    EVE_FORCEINLINE auto is_less_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
    {
      if constexpr( scalar_value<T> && scalar_value<U> )  return as_logical_t<T>(a < b);
      else                                                return a < b;
    }
  }
}
