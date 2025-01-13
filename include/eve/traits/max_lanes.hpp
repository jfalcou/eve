//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve
{
  namespace detail
  {
    template<typename... Ts>
    consteval auto compute_max_lanes()
    {
      std::ptrdiff_t cards[] = { cardinal_v<Ts>... };

      auto max_card = cards[0];
      for(auto c : cards) max_card = max_card < c ? c : max_card;

      return max_card;
    }
  }

  //================================================================================================
  //! @addtogroup traits
  //! @{
  //!  @var max_lanes
  //!
  //!  @tparam Ts Types to process
  //!
  //!  @brief A meta function for getting a maximum lane count of given wide or scalar types.
  //! @}
  //================================================================================================
  template <typename... Ts>
  inline constexpr auto max_lanes_v = detail::compute_max_lanes<Ts...>();

  //================================================================================================
  //! @addtogroup traits
  //! @{
  //!  @var max_lanes
  //!
  //!  @tparam Ts Types to process
  //!
  //!  @brief The cardinal type of the maximum lane count of given wide or scalar types.
  //! @}
  //================================================================================================
  template <typename... Ts>
  using max_lanes_t = fixed<max_lanes_v<Ts...>>; 
}
