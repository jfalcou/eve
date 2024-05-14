//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/cardinal.hpp>
#include <eve/concept/vectorized.hpp>

namespace eve
{
  namespace detail
  {
    template<typename... Ts>
    consteval auto lanes_check()
    {
      // Find largest lanes as a reference
      std::ptrdiff_t cards[] = { cardinal_v<Ts>... };

      auto max_card = cards[0];
      for(auto c : cards) max_card = max_card < c ? c : max_card;

      // Check all lanes is either 1 or equal to max_card
      for(auto c : cards)
      {
        if(c != 1 && c != max_card)
            return false;
      }
      return true;
    }
  }

  //================================================================================================
  //! @addtogroup traits
  //! @{
  //!  @var same_lanes_or_scalar
  //!
  //!  @tparam Ts Type to process
  //!
  //!  @brief Checks that all types `Ts` are either scalar or share a common number of lanes.
  //!
  //!  **Required header:** `#include <eve/traits.hpp>`
  //! @}
  //================================================================================================
  template<typename... Ts>
  inline constexpr bool same_lanes_or_scalar  = detail::lanes_check<Ts...>();

  //================================================================================================
  //! @addtogroup traits
  //! @{
  //!  @var same_lanes
  //!
  //!  @tparam T0 [SIMD Type](@ref eve::simd_value)  to process.
  //!  @tparam Ts [SIMD Types](@ref eve::simd_value) to process.
  //!
  //!  @brief Checks that all SIMD types `Ts` share a common number of lanes.
  //!
  //!  **Required header:** `#include <eve/traits.hpp>`
  //! @}
  //================================================================================================
  template<simd_value T0, simd_value... Ts>
  inline constexpr bool same_lanes = ((cardinal_v<T0> == cardinal_v<Ts>) && ... && true);
}
