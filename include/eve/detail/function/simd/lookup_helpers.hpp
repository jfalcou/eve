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

namespace eve::detail
{
  // shift to apply on large integers lookup index
  template<typename I>
  inline constexpr auto shift = []() {
    if constexpr( sizeof(I) == 2 )
    {
      return 1;
    }
    else if constexpr( sizeof(I) == 4 )
    {
      return 2;
    }
    else if constexpr( sizeof(I) == 8 )
    {
      return 3;
    }
  }();

  // generator for byte index shuffling for large integer
  template<typename I, bool isLittleEndian = true>
  inline constexpr auto repeater = [](auto i, auto) {
    constexpr auto o = isLittleEndian ? 0 : (sizeof(I) - 1);
    return o + sizeof(I) * (i / sizeof(I));
  };

  // large integer offset
  template<typename I, bool isLittleEndian = true>
  inline constexpr auto offset = []() {
    if constexpr( isLittleEndian )
    {
      if constexpr( sizeof(I) == 2 )
      {
        return 0x0100;
      }
      else if constexpr( sizeof(I) == 4 )
      {
        return 0x03020100;
      }
      else if constexpr( sizeof(I) == 8 )
      {
        return 0x0706050403020100ULL;
      }
    }
    else
    {
      if constexpr( sizeof(I) == 2 )
      {
        return 0x0001;
      }
      else if constexpr( sizeof(I) == 4 )
      {
        return 0x00010203;
      }
      else if constexpr( sizeof(I) == 8 )
      {
        return 0x0001020304050607ULL;
      }
    }
  }();
}
