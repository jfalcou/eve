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
  //! @addtogroup core
  //! @{
  //! @var diff_of_prod
  //!
  //! @brief Callable object computing the diff_of_prod operation.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the diff_of_prod operation                                      |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U > auto operator()( T x, U y, V z, W t ) const noexcept requires compatible< T, U, V, W>;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`, `z`, `t`:   [values](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!computes [elementwise](@ref glossary_elementwise) accurately x*y-z*t:
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/diff_of_prod.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct diff_of_prod_; }
  template<> struct supports_conditional<tag::diff_of_prod_> : std::false_type {};

  EVE_MAKE_CALLABLE(diff_of_prod_, diff_of_prod);
}

#include <eve/module/core/regular/impl/diff_of_prod.hpp>
