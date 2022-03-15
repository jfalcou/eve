//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>

namespace eve::detail
{
   //================================================================================================
  // Extract value
  //================================================================================================
  template<typename T, typename N>
  EVE_FORCEINLINE logical<T> extract(logical<wide<T,N>> const& p, std::size_t i) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    if constexpr( !abi_t<T, N>::is_wide_logical )
    {
      using i_t = typename logical<wide<T,N>>::storage_type::type;
      return p.storage().value & (i_t(1) << i);
    }
    else
    {
      // g++ need that
      logical<T> data[N::value];
      auto s = p.storage();
      std::memcpy(&data[0],&s,sizeof(data));
      return data[i];
    }
  }

  //================================================================================================
  // Insert value
  //================================================================================================
  template<typename T, typename N>
  EVE_FORCEINLINE void insert(logical<wide<T,N>>& p, std::size_t i, auto v) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    if constexpr( !abi_t<T, N>::is_wide_logical )
    {
      using i_t = typename logical<wide<T,N>>::storage_type::type;
      p.storage().value = (p.storage().value & ~(i_t(1)<<i)) | ((v ? i_t(1) : 0)<<i);
    }
    else
    {
      auto m = p.bits();
      m.set(i, logical<T>(v).bits());
      p = bit_cast(m, as(p));
    }
  }
}
