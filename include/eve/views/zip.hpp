//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/views/zip.hpp>

namespace eve::views
{
  //================================================================================================
  //! @addtogroup eve.views
  //! @{
  //!    @var zip
  //!    @brief a shorthand for `eve::algo::views::zip`.
  //!
  //!    @struct zip_iterator
  //!    @brief a shorthand for `eve::algo::views::zip_iterator`
  //!
  //!    @struct zip_range
  //!    @brief a shorthand for `eve::algo::views::zip_range`
  //! }@
  //================================================================================================

  using eve::algo::views::zip;
  using eve::algo::views::zip_iterator;
  using eve::algo::views::zip_range;
}
