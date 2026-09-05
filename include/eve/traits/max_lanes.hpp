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
  namespace _
  {
    template<typename... Ts>
    consteval auto compute_max_lanes()
    {
      std::ptrdiff_t max = 0;
      return ((max = (max > cardinal_v<Ts> ? max : cardinal_v<Ts>)), ...);
    }
  }

  //================================================================================================
  //! @addtogroup eve_traits
  //! @{
  //!  @var max_lanes_v
  //!
  //!  @tparam Ts Types to process
  //!
  //!  @brief A meta function for getting a maximum lane count of given wide or scalar types.
  //! @}
  //================================================================================================
  template <typename... Ts>
  inline constexpr auto max_lanes_v = _::compute_max_lanes<Ts...>();

  //================================================================================================
  //! @addtogroup eve_traits
  //! @{
  //!  @typedef max_lanes_t
  //!
  //!  @tparam Ts Types to process
  //!
  //!  @brief The cardinal type of the maximum lane count of given wide or scalar types.
  //! @}
  //================================================================================================
  template <typename... Ts>
  using max_lanes_t = fixed<max_lanes_v<Ts...>>;
}
