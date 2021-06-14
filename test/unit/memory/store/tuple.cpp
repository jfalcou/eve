//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/memory/aligned_ptr.hpp>
#include <eve/function/store.hpp>

#include <array>
#include <numeric>
#include <utility>

namespace
{

template<typename T>
using tuple_t = kumi::tuple<std::int8_t,T,double>;

//==================================================================================================
// store tests
//==================================================================================================
EVE_TEST_TYPES( "Check store behavior with aligned pointers", eve::test::scalar::all_types)
<typename T>(eve::as_<T>)
{
  using s_t = tuple_t<T>;
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

  constexpr auto alg0 = eve::alignment_v< std::tuple_element_t<0,typename w_t::storage_type> >;
  constexpr auto alg2 = eve::alignment_v< std::tuple_element_t<2,typename w_t::storage_type> >;

  alignas(alg0) std::array<std::int8_t, w_t::size()> target0, ctarget0;
                std::array<T          , w_t::size()> target1, ctarget1;
  alignas(alg2) std::array<double     , w_t::size()> target2, ctarget2;

  auto dst = kumi::make_tuple ( eve::as_aligned(&target0[0], eve::cardinal_t<w_t>{})
                              , &target1[0]
                              , eve::as_aligned(&target2[0], eve::cardinal_t<w_t>{})
                              );

  eve::store(data, dst);

  TTS_ALL_EQUAL(target0, ref0);
  TTS_ALL_EQUAL(target1, ref1);
  TTS_ALL_EQUAL(target2, ref2);

  auto cdst = kumi::make_tuple( eve::as_aligned(&ctarget0[0], eve::cardinal_t<w_t>{})
                              , &ctarget1[0]
                              , eve::as_aligned(&ctarget2[0], eve::cardinal_t<w_t>{})
                              );

  eve::store[eve::ignore_last(w_t::size()/2)](data, cdst);

  for(int i = 0; i < w_t::size()/2; ++i)
  {
    TTS_EQUAL(ctarget0[i], ref0[i]);
    TTS_EQUAL(ctarget1[i], ref1[i]);
    TTS_EQUAL(ctarget2[i], ref2[i]);
  }
};

}
