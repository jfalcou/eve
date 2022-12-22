//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/algo/algo/views/map.hpp>

namespace eve::views
{
  //================================================================================================
  //! @addtogroup views
  //! @{
  //!
  //!    @var map_load_op
  //!    @brief a shorthand for `eve::algo::views::map_load_op`.
  //!
  //!    @var map_store_op
  //!    @brief a shorthand for `eve::algo::views::map_store_op`.
  //!
  //!    @var map
  //!    @brief a shorthand for `eve::algo::views::map`.
  //!
  //!    @var map_convert
  //!    @brief a shorthand for `eve::algo::views::map_convert`
  //!
  //!    @struct map_iterator
  //!    @brief a shorthand for `eve::algo::views::map_iterator`
  //!
  //!    @struct map_range
  //!    @brief a shorthand for `eve::algo::views::map_range`
  //! @}
  //================================================================================================
  using eve::algo::views::map_load_op;
  using eve::algo::views::map_store_op;
  using eve::algo::views::map;
  using eve::algo::views::map_convert;
  using eve::algo::views::map_iterator;
  using eve::algo::views::map_range;
}
