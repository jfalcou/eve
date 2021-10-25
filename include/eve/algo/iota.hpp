//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/copy.hpp>
#include <eve/algo/views/iota.hpp>

namespace eve::algo
{
  //================================================================================================
  //! @addtogroup eve.algo
  //! @{
  //!  @var iota
  //!
  //!  @brief version of `std::iota`
  //!  For conversion/overflow behaviour, should follow the standard.
  //!
  //!  **Required header:** `#include <eve/algo/iota.hpp>`
  //! @}
  //================================================================================================

  template <typename TraitsSupport>
  struct iota_ : TraitsSupport
  {
    template <relaxed_range Rng, typename T>
    EVE_FORCEINLINE void operator()(Rng&& rng, T value) const
    {
      algo::copy[TraitsSupport::get_traits()](views::iota(value), rng);
    }
  };

  inline constexpr auto iota = function_with_traits<iota_>[copy.get_traits()];
}
