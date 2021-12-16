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
  //! @addtogroup special
  //! @{
  //! @var exp_int
  //!
  //! @brief Callable object computing the exp_int function.
  //!
  //! **Required header:** `#include <eve/function/exp_int.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the exp_int operation   |
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/exp_int.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(exp_int_, exp_int);
}

#include <eve/module/special/regular/impl/exp_int.hpp>
