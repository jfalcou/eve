//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <bitset>

namespace eve::detail
{
  //================================================================================================
  // Logical to Bits
  //================================================================================================
  template<typename Wide>
  EVE_FORCEINLINE auto to_bits( cpu_ const&, Wide const& p ) noexcept
  {
    using type = typename Wide::bits_type;

    if constexpr ( has_aggregated_abi_v<Wide> )
    {
      auto [l, h] = p.slice();
      return type{l.bits(), h.bits()};
    }
    else
    {
      return bit_cast(p, as<type>{});
    }
  }

  //================================================================================================
  // Logical to Mask
  //================================================================================================
  template<typename Wide>
  EVE_FORCEINLINE auto to_mask(cpu_ const&, Wide const& p ) noexcept
  {
    using type = typename Wide::mask_type;

    if constexpr ( has_aggregated_abi_v<Wide> )
    {
      auto [l, h] = p.slice();
      return type{l.mask(), h.mask()};
    }
    else
    {
      return bit_cast(p, as<type>{});
    }
  }

  //================================================================================================
  // Logical to Bitmap
  //================================================================================================
  template<typename Wide>
  EVE_FORCEINLINE auto to_bitmap( cpu_ const&, Wide const& p ) noexcept
  {
    if constexpr(Wide::size() <= 64)
    {
      if constexpr( has_aggregated_abi_v<Wide> )
      {
        std::size_t res{0};

        [&]<std::size_t... I>(std::index_sequence<I...> const&)
        {
          auto s = p.storage();
          ((res |= ((s.template get<I>()).bitmap().to_ullong() << I*s.template get<I>().size())),...);
        }(std::make_index_sequence<Wide::storage_type::replication>{});

        return std::bitset<Wide::size()>{res};
      }
      else
      {
        std::size_t res{0};
        //using t_t = make_integer_t<std::max(Wide::size()/8,std::ptrdiff_t{1}),unsigned>;
        detail::apply<Wide::size()>( [&](auto... I) { ((res|=(std::size_t{p.get(I)} << I)),...); });
        return std::bitset<Wide::size()>{res};
      }
    }
    else
    {
      std::bitset<Wide::size()> res{0};
      detail::apply<Wide::size()>( [&](auto... I) { (res.set(I,p.get(I)),...); });
      return res;
    }
  }
}
