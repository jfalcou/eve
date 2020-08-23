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
#include <eve/detail/alias.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/traits/element_type.hpp>

namespace eve::detail
{
  //================================================================================================
  // Extract value
  //================================================================================================
  template<typename Storage, typename Wide>
  EVE_FORCEINLINE auto extract( cpu_ const&, as_<Wide> const&
                              , Storage const& p, std::size_t i
                              ) noexcept
  {
    using type = element_type_t<Wide>;

    if constexpr( has_aggregated_abi_v<Wide> )
    {
      auto ptr = reinterpret_cast<detail::alias_t<type> const *>(&p.segments[0]);
      return ptr[i];
    }
    else if constexpr( has_emulated_abi_v<Wide> )
    {
      return p[i];
    }
    else
    {
      auto ptr = reinterpret_cast<detail::alias_t<type> const *>(&p);
      return ptr[i];
    }
  }

  //================================================================================================
  // Insert value
  //================================================================================================
  template<typename Storage, typename Wide, typename Value>
  EVE_FORCEINLINE void insert ( cpu_ const&, as_<Wide> const&
                              , Storage& p, std::size_t i, Value v
                              ) noexcept
  {
    using type = element_type_t<Wide>;

    if constexpr( has_aggregated_abi_v<Wide> )
    {
      auto ptr = reinterpret_cast<detail::alias_t<type>*>(&p.segments[0]);
      ptr[i] = v;
    }
    else if constexpr( has_emulated_abi_v<Wide> )
    {
      p[i] = v;
    }
    else
    {
      auto ptr = reinterpret_cast<detail::alias_t<type>*>(&p);
      ptr[i] = v;
    }
  }
}
