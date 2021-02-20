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
  inline constexpr int regular_mov  =  2;
  inline constexpr int half_mov0    =  1;
  inline constexpr int half_0mov    = -1;

  template<int O, int... I> inline constexpr int is_mov = []()
  {
    constexpr int idx[] = {I...};
    constexpr int  c    = sizeof...(I)/2;

    bool ok = true;
    for(int i=0;i<c;++i) ok = ok && (idx[i] == i+O) && (idx[i+c] == -1);
    if(ok)  return half_mov0;

    ok = true;
    for(int i=0;i<c;++i) ok = ok && (idx[i] == -1)  && (idx[i+c] == i+O);
    if(ok)  return half_0mov;

    ok = true;
    for(int i=0;i<c;++i) ok = ok && (idx[i] == i+O) && (idx[i+c] == i+O);
    return ok ? regular_mov : 0;
  }();

  template<int... I> inline constexpr bool is_movhl = (is_mov<sizeof...(I)/2 , I...> != 0);
  template<int... I> inline constexpr bool is_movlh = (is_mov<0              , I...> != 0);
}
