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

namespace eve::detail
{
   //================================================================================================
  // Extract value
  //================================================================================================
  template<typename T, typename N, x86_abi ABI>
  EVE_FORCEINLINE logical<T> extract(logical<wide<T,N,ABI>> const& p, std::size_t i) noexcept
  {
    if constexpr( !ABI::is_wide_logical )
    {
      using i_t = typename logical<wide<T,N,ABI>>::storage_type::type;
      return p.storage().value & (i_t(1) << i);
    }
    else
    {
      return at_begin(p)[i];
    }
  }

  //================================================================================================
  // Insert value
  //================================================================================================
  template<typename T, typename N, x86_abi ABI>
  EVE_FORCEINLINE void insert(logical<wide<T,N,ABI>>& p, std::size_t i, auto v) noexcept

  {
    if constexpr( !ABI::is_wide_logical )
    {
      using i_t = typename logical<wide<T,N,ABI>>::storage_type::type;
      p.storage().value |= (v ? (i_t(1)<<i) : 0);
    }
    else
    {
      [[maybe_unused]] auto& s = p.storage();
      auto ptr = reinterpret_cast<detail::alias_t<logical<T>>*>(&p);
      ptr[i] = v;
    }
  }
}
