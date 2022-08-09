//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/alias.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/traits/element_type.hpp>
#include <eve/as.hpp>
#include <cstring>

namespace eve::detail
{
  //================================================================================================
  // Extract value
  //================================================================================================
  template<typename Wide>
  EVE_FORCEINLINE auto extract(Wide const& p, std::size_t i) noexcept
  {
    using abi_t = typename Wide::abi_type;

    if constexpr( has_bundle_abi_v<Wide> )
    {
      return kumi::apply( [=](auto const&... m)
                          {
                            return typename Wide::value_type{ m.get(i)... };
                          }
                          , p.storage()
                        );
    }
    else if constexpr( has_aggregated_abi_v<Wide> && !abi_t::is_wide_logical )
    {
      constexpr auto sz = Wide::size()/2;
      if(i<sz)  return extract(p.slice(lower_),i);
      else      return extract(p.slice(upper_),i-sz);
    }
    else
    {
      // g++ need that
      typename Wide::value_type data[Wide::size()];
      auto s = p.storage();
      std::memcpy((char*)(&data[0]),(char*)(&s),sizeof(data));
      return data[i];
    }
  }

  //================================================================================================
  // Insert value
  //================================================================================================
  template<typename Wide, typename Value>
  EVE_FORCEINLINE void insert(Wide& p, std::size_t i, Value v) noexcept
  {
    using type = element_type_t<Wide>;

    if constexpr( has_aggregated_abi_v<Wide> )
    {
      using abi_t = typename Wide::abi_type;

      if constexpr( abi_t::is_wide_logical )
      {
        auto ptr = reinterpret_cast<detail::alias_t<type>*>(&p.storage().segments[0]);
        ptr[i] = v;
      }
      else
      {
        constexpr auto sz = Wide::size() / 2;
        auto[l,h] = p.slice();

        if(i<sz)  insert(l,i,v);
        else      insert(h,i-sz,v);

        p = Wide{l,h};
      }
    }
    else if constexpr( has_emulated_abi_v<Wide> )
    {
      p.storage()[i] = v;
    }
    else if constexpr( has_bundle_abi_v<Wide> )
    {
      kumi::for_each( [i](auto& m, auto w) { m.set(i,w); }, p.storage(), v);
    }
    else
    {
      // g++ need that
      typename Wide::value_type data[Wide::size()];
      auto s = p.storage();
      std::memcpy((char*)(&data[0]),(char*)(&s),sizeof(data));
      data[i] = v;
      std::memcpy((char*)(&p),(char*)(&data[0]),sizeof(data));
    }
  }
}
