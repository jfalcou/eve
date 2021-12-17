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
  //! @var lfactorial
  //!
  //! @brief Callable object computing natural logarithm of the factorial of  unsigned integers
  //! \f$\displaystyle \log n! = \sum_{i=1}^n \log i\f$.
  //!
  //! **Required header:** `#include <eve/function/lfactorial.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` |  lfactorial of  unsigned integers                          |
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
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/combinatorial/lfactorial.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct lfactorial_; }
  template<> struct supports_conditional<tag::lfactorial_> : std::false_type {};

  EVE_MAKE_CALLABLE(lfactorial_, lfactorial);
}

#include <eve/module/combinatorial/regular/impl/lfactorial.hpp>
