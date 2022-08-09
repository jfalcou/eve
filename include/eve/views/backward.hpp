//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/algo/views/backward.hpp>

namespace eve::views
{
  //================================================================================================
  //! @addtogroup views
  //! @{
  //!
  //!    @var backward
  //!    @brief a shorthand for `eve::algo::views::backward`.
  //!
  //!    @struct backward_iterator
  //!    @brief a shorthand for `eve::algo::views::backward_iterator`
  //!
  //!    @struct backward_range
  //!    @brief a shorthand for `eve::algo::views::backward_range`
  //!
  //! }@
  //================================================================================================


  using eve::algo::views::backward;
  using eve::algo::views::backward_iterator;
  using eve::algo::views::backward_range;
}
