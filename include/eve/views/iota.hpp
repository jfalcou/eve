//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/views/iota.hpp>

namespace eve::views
{
  //================================================================================================
  //! @addtogroup views
  //! @{
  //!
  //!    @var iota
  //!    @brief a shorthand for `eve::algo::views::iota`.
  //!
  //!    @var iota_with_step
  //!    @brief a shorthand for `eve::algo::views::iota_with_step`.
  //!
  //!    @struct iota_with_step_iterator
  //!    @brief a shorthand for `eve::algo::views::iota_with_step_iterator`
  //!
  //! }@
  //================================================================================================
  using eve::algo::views::iota;
  using eve::algo::views::iota_with_step;
  using eve::algo::views::iota_with_step_iterator;
}
