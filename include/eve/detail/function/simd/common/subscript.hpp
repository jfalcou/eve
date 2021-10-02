//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/alias.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/traits/element_type.hpp>
#include <eve/as.hpp>

namespace eve::detail
{
  //================================================================================================
  // Extract value
  //================================================================================================
  template<typename Wide>
  EVE_FORCEINLINE auto at_begin ( Wide const& p ) noexcept
  {
    using type = element_type_t<Wide>;

    if constexpr( has_aggregated_abi_v<Wide> )
    {
      return reinterpret_cast<detail::alias_t<type> const *>(&p.storage().segments[0]);
    }
    else if constexpr( has_emulated_abi_v<Wide> )
    {
      return p.storage().data();
    }
    else
    {
      [[maybe_unused]] auto const& s = p.storage();
      return reinterpret_cast<detail::alias_t<type> const *>(&p);
    }
  }

  template<typename Wide>
  EVE_FORCEINLINE auto at_begin ( Wide& p ) noexcept
  {
    using type = element_type_t<Wide>;

    if constexpr( has_aggregated_abi_v<Wide> )
    {
      return reinterpret_cast<detail::alias_t<type> *>(&p.storage().segments[0]);
    }
    else if constexpr( has_emulated_abi_v<Wide> )
    {
      return p.storage().data();
    }
    else
    {
      [[maybe_unused]] auto& s = p.storage();
      return reinterpret_cast<detail::alias_t<type> *>(&s);
    }
  }

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
                            return typename Wide::value_type{ at_begin(m)[i]... };
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
      return at_begin(p)[i];
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
      auto ptr = reinterpret_cast<detail::alias_t<type>*>(&p.storage());
      ptr[i] = v;
    }
  }
}
