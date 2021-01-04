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
  template<typename Storage, typename Wide, typename ABI>
  EVE_FORCEINLINE auto at_begin ( ABI const&, as_<Wide> const&, Storage const& p ) noexcept
  {
    using type = element_type_t<Wide>;

    if constexpr( has_aggregated_abi_v<Wide> )
    {
      return reinterpret_cast<detail::alias_t<type> const *>(&p.segments[0]);
    }
    else if constexpr( has_emulated_abi_v<Wide> )
    {
      return p.data();
    }
    else
    {
      return reinterpret_cast<detail::alias_t<type> const *>(&p);
    }
  }

  template<typename Storage, typename Wide, typename ABI>
  EVE_FORCEINLINE auto at_begin ( ABI const&, as_<Wide> const&, Storage & p ) noexcept
  {
    using type = element_type_t<Wide>;

    if constexpr( has_aggregated_abi_v<Wide> )
    {
      return reinterpret_cast<detail::alias_t<type> *>(&p.segments[0]);
    }
    else if constexpr( has_emulated_abi_v<Wide> )
    {
      return p.data();
    }
    else
    {
      return reinterpret_cast<detail::alias_t<type> *>(&p);
    }
  }

  //================================================================================================
  // Extract value
  //================================================================================================
  template<typename Storage, typename Wide, typename ABI>
  EVE_FORCEINLINE element_type_t<Wide> extract( ABI const& arch, as_<Wide> const& tgt
                                              , Storage const& p, std::size_t i
                                              ) noexcept
  {
    return at_begin(arch,tgt,p)[i];
  }

  //================================================================================================
  // Insert value
  //================================================================================================
  template<typename Storage, typename Wide, typename Value, typename ABI>
  EVE_FORCEINLINE void insert ( ABI const&, as_<Wide> const&
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
