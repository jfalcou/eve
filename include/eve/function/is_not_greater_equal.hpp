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
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * `definitely`
  //!
  //!     **Required header:**  #include <eve/function/fuzzy/is_not_greater_equal.hpp>
  //!  
  //!     The expression `definitely(is_not_greater_equal)(x, y, t)` where `x` and `y` must be
  //!      floating point values, evals to true if and only if and only if `x` is definitely not greater or equal to `y`.
  //!      This means that the pair `x, y` is unordered or:
  //!  
  //!      - if `t` is a floating_value then  \f$(x \le y - t \max(|x|, |y|))\f$
  //!      - if `t` is a positive integral_value then \f$(x \le \mbox{prev}(y, t)\f$;
  //!      - if `t` is omitted then the tolerance `t` default to `3*eps(as(x))`.
  //!  
  //!  The result type is the [compatibility result](../../concept.html#compatibility) of the two parameters.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/is_not_greater_equal.cpp
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct is_not_greater_equal_; }
  template<> struct supports_conditional<tag::is_not_greater_equal_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(is_not_greater_equal_, is_not_greater_equal);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/is_not_greater_equal.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/is_not_greater_equal.hpp>
#endif
