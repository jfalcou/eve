//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/traits/value_type.hpp>

#include <vector>

TTS_CASE( "Check for value_type, iterator")
{
  TTS_TYPE_IS(eve::value_type_t<int*>,                       int);
  TTS_TYPE_IS(eve::value_type_t<int const*>,                 int);
  TTS_TYPE_IS(eve::value_type_t<std::vector<int>::iterator>, int);

  TTS_TYPE_IS((eve::value_type_t<kumi::tuple<int*, float*>>),
              (kumi::tuple<int, float>));

  TTS_TYPE_IS((eve::value_type_t<
                 kumi::tuple<kumi::tuple<int*, float*>,
                             int*>
               >),
              (kumi::tuple<kumi::tuple<int, float>, int>));
};

TTS_CASE( "Check for value_type, range")
{
  {
    int x[5];
    TTS_TYPE_IS(eve::value_type_t<decltype(x)>, int);
  }
  TTS_TYPE_IS(eve::value_type_t<std::vector<int>>, int);
};
