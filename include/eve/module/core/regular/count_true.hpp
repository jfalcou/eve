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
  //! @addtogroup reduction
  //! @{
  //! @var count_true
  //!
  //! @brief Callable object computing the count_true value.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of the count_true value                    |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  int operator()(value auto x) const noexcept;
  //!  int operator()(instance_of<top_bits> auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](@ref eve::value).
  //!`x`:   [top_bits](@ref eve::top_bits)
  //!
  //! **Return value**
  //!
  //!  an int value: the number of non zero elements in `x`.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/count_true.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(count_true_, count_true);
}

#include <eve/arch.hpp>
#include <eve/module/core/regular/impl/count_true.hpp>
