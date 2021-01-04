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
  template<typename Storage, typename Wide, x86_abi ABI>
  EVE_FORCEINLINE element_type_t<Wide> extract( ABI const& arch, as_<logical<Wide>> const& tgt
                                              , Storage const& p, std::size_t i
                                              ) noexcept
  {
    if constexpr( !ABI::is_wide_logical )
    {
      using i_t = typename Storage::type;
      return p.value & (i_t(1) << i);
    }
    else
    {
      return extract(cpu_{},tgt,p,i);
    }
  }

  //================================================================================================
  // Insert value
  //================================================================================================
  template<typename Storage, typename Wide, typename Value, x86_abi ABI>
  EVE_FORCEINLINE void insert ( ABI const&, as_<logical<Wide>> const& tgt
                              , Storage& p, std::size_t i, Value v
                              ) noexcept
  {
    if constexpr( !ABI::is_wide_logical )
    {
      using i_t = typename Storage::type;
      p.value |= (v ? (i_t(1)<<i) : 0);
    }
    else
    {
      insert(cpu_{},tgt,p,i,v);
    }
  }
}
