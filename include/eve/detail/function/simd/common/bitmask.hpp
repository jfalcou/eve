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
    return bit_cast(p, as_<type>{});
  }

  //================================================================================================
  // Logical to Mask
  //================================================================================================
  template<typename Wide>
  EVE_FORCEINLINE auto to_mask( cpu_ const&, Wide const& p ) noexcept
  {
    using type = typename Wide::mask_type;
    return bit_cast(p, as_<type>{});
  }

  //================================================================================================
  // Logical to Bitmap
  //================================================================================================
  template<typename Wide>
  EVE_FORCEINLINE auto to_bitmap( cpu_ const&, Wide const& p ) noexcept
  {
    if constexpr(Wide::static_size <= 64)
    {
      if constexpr( has_aggregated_abi_v<Wide> )
      {
        std::size_t res{0};

        [&]<std::size_t... I>(std::index_sequence<I...> const&)
        {
          auto s = p.storage();
          ((res |= ((s.template get<I>()).bitmap().to_ullong() << I*s.template get<I>().size())),...);
        }(std::make_index_sequence<Wide::storage_type::replication>{});

        return std::bitset<Wide::static_size>{res};
      }
      else
      {
        std::size_t res{0};
        detail::apply<Wide::static_size>( [&](auto... I) { ((res|=(p[I] << I)),...); });
        return std::bitset<Wide::static_size>{res};
      }
    }
    else
    {
      std::bitset<Wide::static_size> res{0};
      detail::apply<Wide::static_size>( [&](auto... I) { (res.set(I,p[I]),...); });
      return res;
    }
  }
}
