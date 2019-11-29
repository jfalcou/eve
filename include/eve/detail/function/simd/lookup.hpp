//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_LOOKUP_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_LOOKUP_HPP_INCLUDED

namespace eve::detail
{
  // shift to apply on large integers lookup index
  template<typename I> inline
  constexpr auto shift = []() {
                                return  sizeof(I) == 2 ? 1 : (sizeof(I) == 4 ? 2 : 3);
                              }();

  // generator for byte index shuffling for large integer
  template<typename I> inline
  constexpr auto repeater = [](auto i, auto) { return sizeof(I)*(i/sizeof(I)); };

  // large integer offset
  template<typename I> inline
  constexpr auto offset   = []()
                            {
                              return  sizeof(I) == 2 ? 0x0100 :
                                      sizeof(I) == 4 ? 0x03020100 : 0x0706050403020100ULL;
                            }();
}

#endif
