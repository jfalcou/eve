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
  //! @addtogroup combinatorial
  //! @{
  //! @var factorial
  //!
  //! @brief Callable object computing factorial of  unsigned integers \f$\displaystyle n! = \prod_{i=1}^n i\f$.
  //!
  //! **Required header:** `#include <eve/function/factorial.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` |  factorial of  unsigned integers                           |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()( value auto n ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`n`:   [value](@ref eve::value) must be positive and flint (if floating point).
  //!
  //! **Return value**
  //!
  //! If the entry is an [integral_value](eve::integral_value), the result [element type](eve::element_type)
  //! is always double to try to avoid overflow and its cardinal is the same as the entry in case of an simd call.
  //!
  //! If the entry is a [floating_point_value](eve::floating_point_value) which must be a flint,
  //! the result is of the same type as the entry.
  //!
  //!@warning
  //!    this function will overflow as soon as the input is greater than 171 for integral or double entries
  //!    and if the entry is greater than 34 for float.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/combinatorial/factorial.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct factorial_; }
  template<> struct supports_conditional<tag::factorial_> : std::false_type {};

  EVE_MAKE_CALLABLE(factorial_, factorial);
}

#include <eve/module/combinatorial/regular/impl/factorial.hpp>
