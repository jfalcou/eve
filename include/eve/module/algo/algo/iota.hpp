//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/algo/algo/copy.hpp>
#include <eve/module/algo/algo/views/iota.hpp>

namespace eve::algo
{
  //================================================================================================
  //! @addtogroup algos
  //! @{
  //!  @var iota
  //!
  //!  @brief SIMD version of `std::iota`
  //!  For conversion/overflow behaviour, should follow the standard.
  //!
  //!  **Required header:** `#include <eve/module/algo/algo/iota.hpp>`
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
