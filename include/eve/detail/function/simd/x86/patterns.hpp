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

namespace eve::detail
{
  //================================================================================================
  // Detects movhl/lh variants
  //================================================================================================
  template<int O, int... I> inline constexpr bool is_mov = []()
  {
    int idx[] = {I...};
    int  c  = sizeof...(I)/2;
    bool ok = true;

    for(int i=0;i<c;++i)
      ok = ok && (idx[i] == i+O) && (idx[i+c] == i+O);

    return ok;
  }();

  template<int... I> inline constexpr bool is_movhl = is_mov<sizeof...(I)/2 , I...>;
  template<int... I> inline constexpr bool is_movlh = is_mov<0              , I...>;

// else if constexpr(q == pattern<2,3,-1,-1>)
// {
//   return bit_cast( o_t{_mm_movehl_ps(i_t(0),r)}, as_<that_t>{});
// }
// else if constexpr(q == pattern<-1,-1,2,3>)
// {
//   return bit_cast( o_t{_mm_movehl_ps(r,i_t(0))}, as_<that_t>{});
// }
// else if constexpr((q == pattern<2,3,2,3>) || (q == pattern<2,3> && N::value==4))
// {
//   return bit_cast( o_t{_mm_movehl_ps(r,r)}, as_<that_t>{});
// }
}
