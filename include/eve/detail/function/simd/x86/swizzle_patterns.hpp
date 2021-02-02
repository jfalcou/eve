//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018-2021 Joel FALCOU
  Copyright 2018-2021 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/function/simd/common/swizzle_patterns.hpp>
#include <eve/pattern.hpp>

namespace eve::detail
{
  template<typename T, typename N, x86_abi ABI, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto swizzle_pattern(sse2_ const&, wide<T,N,ABI> const& v, Pattern const&)
  {
    constexpr auto sz = Pattern::size(N::value);
    using that_t      = as_wide_t<wide<T,N,ABI>,fixed<sz>>;

    constexpr Pattern q{};

    // Try common patterns first
    if constexpr( !std::same_as<void, decltype(swizzle_pattern(cpu_{},v,q))> )
    {
      return swizzle_pattern(cpu_{},v,q);
    }
    //----------------------------------------------------------------------------------------------
    // SSE2 : float/int32 special cases
    else if constexpr(sizeof(T) == 4)
    {
      using i_t = as_floating_point_t<wide<T,N,ABI>>;
      using o_t = as_floating_point_t<that_t>;
      auto const r = bit_cast(v, as_<i_t>() );

      // MOVLH/MOVHL combo with/without 0s
      if constexpr(q == pattern<0,1,0,1>)
      {
        return bit_cast( o_t{_mm_movelh_ps(r,r)}, as_<that_t>{});
      }
      else if constexpr(q == pattern<0,1,-1,-1>)
      {
        return bit_cast( o_t{_mm_movelh_ps(r,i_t(0))}, as_<that_t>{});
      }
      else if constexpr(q == pattern<-1,-1,0,1>)
      {
        return bit_cast( o_t{_mm_movelh_ps(i_t(0),r)}, as_<that_t>{});
      }
      else if constexpr((q == pattern<2,3,2,3>) || (q == pattern<2,3> && N::value==4))
      {
        return bit_cast( o_t{_mm_movehl_ps(r,r)}, as_<that_t>{});
      }
      else if constexpr(q == pattern<2,3,-1,-1>)
      {
        return bit_cast( o_t{_mm_movehl_ps(i_t(0),r)}, as_<that_t>{});
      }
      else if constexpr(q == pattern<-1,-1,2,3>)
      {
        return bit_cast( o_t{_mm_movehl_ps(r,i_t(0))}, as_<that_t>{});
      }
    }
    //----------------------------------------------------------------------------------------------

    // If all pattern fails, we return void to signify we need to do a proper swizzle
  }
}
