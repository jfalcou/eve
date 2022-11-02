//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/kumi.hpp>

namespace eve
{
  namespace detail
  {
    template<typename T> constexpr auto max_scalar() noexcept
    {
      if constexpr(kumi::product_type<T>)
      {
        return kumi::max_flat(kumi::as_tuple_t<T>{}, [](auto m) { return sizeof(m); });
      }
      else return sizeof(T);
    }
  }

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
  template <typename T>
  constexpr std::size_t max_scalar_size_v = detail::max_scalar<T>();
}
