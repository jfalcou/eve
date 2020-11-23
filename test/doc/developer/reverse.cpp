//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Denis YAROSHEVSKIY
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#if defined(EVE_HW_X86) && !defined(SPY_SIMD_IS_X86_AVX512)
#include "reverse.hpp"

TTS_CASE_TPL( "Check for reverse behavior", float,double )
{
  using type = eve::wide<T>;

  type input( [](auto i, auto size)
              {
                if(i == 0     ) return std::numeric_limits<T>::min();
                if(i == size-1) return std::numeric_limits<T>::max();
                return static_cast<T>(i);
              }
            );

  type expected( [](auto i, auto size)
              {
                if(i == 0     ) return std::numeric_limits<T>::max();
                if(i == size-1) return std::numeric_limits<T>::min();
                return static_cast<T>(size - 1 - i);
              }
            );

  TTS_EQUAL(eve_extra::reverse(input), expected);
}

#endif
