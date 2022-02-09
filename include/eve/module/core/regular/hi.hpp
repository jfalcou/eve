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
  //! @addtogroup ieee754
  //! @{
  //! @var hi
  //!
  //! @brief Callable object computing the higher part of the values.
  //!
  //! **Required header:** #include <eve/module/core.hpp>
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of the higher part of the values           |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()( integral_value auto x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [integral value](@ref eve::integral_value).
  //!
  //! **Return value**
  //!
  //!    Computes the [elementwise](@ref glossary_elementwise) higher half of the  value,
  //!    returning each element as an unsigned integer of half the size of the input element.
  //!
  //!    If you also need the lower part `lohi` is more efficient.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/arithmetic/hi.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(hi_, hi);
}

#include <eve/module/core/regular/impl/hi.hpp>
