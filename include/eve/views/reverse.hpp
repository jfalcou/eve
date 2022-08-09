//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/algo/views/reverse.hpp>

namespace eve::views
{
  //================================================================================================
  //! @addtogroup views
  //! @{
  //!
  //!    @var reverse
  //!    @brief a shorthand for `eve::algo::views::reverse`.
  //!
  //!    @struct reverse_iterator
  //!    @brief a shorthand for `eve::algo::views::reverse_iterator`
  //!
  //!    @struct reverse_range
  //!    @brief a shorthand for `eve::algo::views::reverse_range`
  //!
  //! }@
  //================================================================================================
  using eve::algo::views::reverse;
  using eve::algo::views::reverse_iterator;
  using eve::algo::views::reverse_range;
}
