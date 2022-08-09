//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::detail
{
// shift to apply on large integers lookup index
template<typename I>
inline constexpr auto shift = []()
{
  if constexpr( sizeof(I) == 1 ) return 0;
  else if constexpr( sizeof(I) == 2 ) return 1;
  else if constexpr( sizeof(I) == 4 ) return 2;
  else if constexpr( sizeof(I) == 8 ) return 3;
}();

// generator for byte index shuffling for large integer
template<typename T, typename I, bool isLittleEndian = true>
inline constexpr auto repeater = [](auto i, auto)
{
  auto space = (i / sizeof(T)) + !isLittleEndian;
  return (sizeof(I) * space) - !isLittleEndian;
};

// large integer offset
template<typename I, bool isLittleEndian = true>
inline constexpr auto offset = []()
{
  if constexpr( isLittleEndian )
  {
    if constexpr( sizeof(I) == 1 ) return 0x00;
    else if constexpr( sizeof(I) == 2 ) return 0x0100;
    else if constexpr( sizeof(I) == 4 ) return 0x03020100;
    else if constexpr( sizeof(I) == 8 ) return 0x0706050403020100ULL;
  }
  else
  {
    if constexpr( sizeof(I) == 1 ) return 0x00;
    else if constexpr( sizeof(I) == 2 ) return 0x0001;
    else if constexpr( sizeof(I) == 4 ) return 0x00010203;
    else if constexpr( sizeof(I) == 8 ) return 0x0001020304050607ULL;
  }
}();
}
