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
#include <iostream>

#if defined(EVE_HW_X86) && !defined(SPY_SIMD_IS_X86_AVX512)
#include "reverse.hpp"

template<typename T, typename Test>
void check_all_sizes(Test test)
{
  constexpr int number_of_packs = std::countr_zero(256u / sizeof(T));
  [&]<int... idx>(std::integer_sequence<int, idx...>)
  {
    (test(eve::wide<T, eve::fixed<static_cast<size_t>(1 << idx)>> {}), ...);
  } (std::make_integer_sequence<int, number_of_packs>());
}

TTS_CASE_TPL( "Check for reverse behavior", TTS_NUMERIC_TYPES )
{
  check_all_sizes<T>
  (
    [&]<typename Type>(Type const&)
    {
      std::cout << tts::green("Size: ") << eve::cardinal_v<Type> << " - ";
      using value_type = eve::element_type_t<Type>;

      Type input( [](auto i, auto size)
                    {
                      if(i == size-1) return std::numeric_limits<value_type>::max();
                      if(i == 0     ) return std::numeric_limits<value_type>::min();
                      return static_cast<T>(i);
                    }
                  );

      Type expected( [](auto i, auto size)
                  {
                    if(i == 0     ) return std::numeric_limits<value_type>::max();
                    if(i == size-1) return std::numeric_limits<value_type>::min();
                    return static_cast<T>(size - 1 - i);
                  }
                );

      TTS_EQUAL(eve_extra::reverse(input), expected);
    }
  );
}

#endif
