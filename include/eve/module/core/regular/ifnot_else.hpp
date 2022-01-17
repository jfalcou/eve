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
  //! @addtogroup logical
  //! @{
  //! @var ifnot_else
  //!
  //! @brief Callable object computing the ifnot_else operation.
  //!
  //! **Required header:** `#include <eve/function/ifnot_else.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the ifnot_else operation   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U, value V > auto operator()( T x, U y, V z ) const noexcept
  //!  requires  compatible< U, V >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`, `z`:   [values](@ref eve::value)
  //!
  //! **Return value**
  //!
  //!The call `eve::ifnot_else``(x, y, z)`  performs a choice between the elements of `y` and `z` according to the truth value
  //!of the elements of `x`. It is merely syntaxic sugar for `eve::if_else``(x, z, y)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/ifnot_else.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct ifnot_else_; }
  template<> struct supports_conditional<tag::ifnot_else_> : std::false_type {};

  EVE_MAKE_CALLABLE(ifnot_else_, ifnot_else);
}

#include <eve/module/core/regular/impl/ifnot_else.hpp>
