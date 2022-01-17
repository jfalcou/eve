//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/kumi.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup traits
  //! @{
  //!  @var max_scalar_size_v
  //!
  //!  @tparam T Type to process
  //!
  //!  @brief A meta function for getting a maximum size of scalar.
  //!
  //!         For a product type returns max size of individual fields.
  //!         Otherwise returns sizeof(T)
  //!
  //!   **Required header:** `#include <eve/traits/max_scalar_size.hpp>`,
  //!                        `#include <eve/traits.hpp>`
  //! @}
  //================================================================================================
  namespace detail
  {
    template <typename T>
    constexpr std::size_t max_scalar_size_impl()
    {
      if constexpr ( !kumi::product_type<T> ) return sizeof(T);
      else
      {
        using flat_t = kumi::result::flatten_all_t<T>;

        return kumi::fold_left([]<typename U>(std::size_t cur, U) {
          // Don't want to bring algorithm
          return cur > sizeof(U) ? cur : sizeof(U);
        }, flat_t{}, 0u);
      }
    }
  }

  template <typename T>
  constexpr std::size_t max_scalar_size_v = detail::max_scalar_size_impl<T>();

  namespace detail
  {
    template <typename T>
    constexpr std::size_t min_scalar_size_impl()
    {
      if constexpr ( !kumi::product_type<T> ) return sizeof(T);
      else
      {
        using flat_t = kumi::result::flatten_all_t<T>;

        return kumi::fold_left([]<typename U>(std::size_t cur, U) {
          // Don't want to bring algorithm
          return cur < sizeof(U) ? cur : sizeof(U);
        }, flat_t{}, 0u);
      }
    }
  }

  template <typename T>
  constexpr std::size_t min_scalar_size_v = detail::min_scalar_size_impl<T>();
}
