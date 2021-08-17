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
  //! @var lo
  //!
  //! @brief Callable object computing the lower part of the values.
  //!
  //! **Required header:** `#include <eve/function/lo.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of the lower part of the values   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!   auto operator()( integral_value auto x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [integral value](@ref eve::integral_value).
  //!
  //! **Return value**
  //!
  //!    Computes the [elementwise](@ref glossary_elementwise) lower half of the  value,
  //!    returning each elemnet as an unsigned integer of half the size of the input element.
  //!
  //!    If you also need the higher part `lohi` is more efficient.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/lo.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(lo_, lo);
}

#include <eve/module/real/core/function/regular/generic/lo.hpp>
