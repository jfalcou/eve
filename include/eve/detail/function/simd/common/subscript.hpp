//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/traits/element_type.hpp>

namespace eve::detail
{
  //================================================================================================
  // Extract value
  //================================================================================================
  template<typename Pack>
  EVE_FORCEINLINE auto extract(Pack const & p, std::size_t i) noexcept
  {
    using type = element_type_t<Pack>;
    auto const& data = p.storage();

    if constexpr( has_aggregated_abi_v<Pack> )
    {
      auto ptr = reinterpret_cast<detail::alias_t<type> const *>(&data.segments[0]);
      return ptr[i];
    }
    else
    {
      auto ptr = reinterpret_cast<detail::alias_t<type> const *>(&data);
      return ptr[i];
    }
  }

  //================================================================================================
  // Insert value
  //================================================================================================
  template<typename Pack, typename Value>
  EVE_FORCEINLINE void insert(Pack& p, std::size_t i, Value v) noexcept
  {
    using type = element_type_t<Pack>;
    auto& data = p.storage();

    if constexpr( has_aggregated_abi_v<Pack> )
    {
      auto ptr = reinterpret_cast<detail::alias_t<type>*>(&data.segments[0]);
      ptr[i] = v;
    }
    else
    {
      auto ptr = reinterpret_cast<detail::alias_t<type>*>(&data);
      ptr[i] = v;
    }
  }
}
