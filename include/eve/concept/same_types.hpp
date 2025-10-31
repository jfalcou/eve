//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/kumi.hpp>
#include <eve/traits/cardinal.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/concept/same_lanes.hpp>

namespace eve
{
  namespace detail
  {
    template<typename T0, typename... Ts>
    consteval auto type_check()
    {
      if constexpr (sizeof...(Ts) == 0) return true;
      else                              return (std::same_as<element_type_t<T0>, element_type_t<Ts>> && ...);
    }

    template<kumi::product_type T>
    consteval auto tuple_type_check()
    {
      if constexpr(kumi::sized_product_type<T, 0>) return true;
      else                                         return kumi::homogeneous_product_type<kumi::map_traits_t<element_type, T>>;
    }
  }

  //================================================================================================
  //! @addtogroup traits
  //! @{
  //!  @var same_types
  //!
  //!  @tparam Ts Type to process
  //!
  //!  @brief Checks that all types `Ts` are scalars of a single type `U` or simd_values sharing the
  //!         same lane count and of element type `U`.
  //!
  //!  **Required header:** `#include <eve/concept/same_types.hpp>`
  //! @}
  //================================================================================================
  template<typename... Ts>
  concept same_types = same_lanes_or_scalar<Ts...> && detail::type_check<Ts...>();

  //================================================================================================
  //! @addtogroup traits
  //! @{
  //!  @var same_types_tuple
  //!
  //!  @tparam T Product type to process
  //!
  //!  @brief Checks that all types within a product type are scalars of a single type `U` or
  //!         simd_values sharing the same lane count and of element type `U`.
  //!
  //!  **Required header:** `#include <eve/concept/same_types.hpp>`
  //! @}
  //================================================================================================
  template<typename T>
  concept same_types_tuple = same_lanes_or_scalar_tuple<T> && detail::tuple_type_check<T>();
}
