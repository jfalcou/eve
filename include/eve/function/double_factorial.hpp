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
  //! @addtogroup combinatorial
  //! @{
  //! @var double_factorial
  //!
  //! @brief Callable object computing unsigned integral double_factorial.
  //!
  //! **Required header:** `#include <eve/function/double_factorial.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | unsigned integral double_factorial   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()( unsigned_value auto n ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`n`:   [unsigned value](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!double factorial is defined by \f$\displaystyle (2n)!! = \prod_{i=1}^n (2i)\f$ and \f$\displaystyle (2n+1)!! = \prod_{i=0}^n (2i+1)\f$
  //!
  //! The result element type is always double to try to avoid overflow
  //! and its cardinal is the same as the entry in case of an simd call.
  //!
  //!@warning
  //!    this function will overflow as soon as the input is greater than 300.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/double_factorial.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct double_factorial_; }
  template<> struct supports_conditional<tag::double_factorial_> : std::false_type {};

  EVE_MAKE_CALLABLE(double_factorial_, double_factorial);
}

#include <eve/module/real/combinatorial/function/regular/generic/double_factorial.hpp>
