//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/store.hpp>

#include <array>
#include <numeric>

namespace
{

template<typename T>
using tuple_t = kumi::tuple<std::int8_t,T,double>;

//==================================================================================================
// Aligned store tests
//==================================================================================================
EVE_TEST_TYPES( "Check store behavior with unaligned pointers", eve::test::scalar::all_types)
<typename T>(eve::as_<T>)
{
  using s_t  = tuple_t<T>;
  using w_t = eve::wide<tuple_t<T>>;

  auto const filler = [](auto i, auto)  { return s_t{ static_cast<std::int8_t>('a'+i)
                                                    , static_cast<T>(i + 1)
                                                    , 1.5*(1+i)
                                                    };
                                        };

  w_t data = filler;

  std::array<std::int8_t, w_t::size()> ref0;
  std::array<T          , w_t::size()> ref1;
  std::array<double     , w_t::size()> ref2;

  for(int i = 0; i < w_t::size(); ++i)
  {
    ref0[i] = static_cast<std::int8_t>('a'+i);
    ref1[i] = static_cast<T>(i + 1);
    ref2[i] = 1.5*(1+i);
  }

  std::array<std::int8_t, w_t::size()> target0;
  std::array<T          , w_t::size()> target1;
  std::array<double     , w_t::size()> target2;

  auto dst = kumi::make_tuple(&target0[0], &target1[0], &target2[0]);

  eve::store(data, dst);

  TTS_ALL_EQUAL(target0, ref0);
  TTS_ALL_EQUAL(target1, ref1);
  TTS_ALL_EQUAL(target2, ref2);
};

}
