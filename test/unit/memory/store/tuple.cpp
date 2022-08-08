//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/memory/soa_ptr.hpp>

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
TTS_CASE_TPL( "Check store behavior with soa_ptr", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
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

  auto dst = eve::soa_ptr    ( eve::as_aligned(&target0[0], eve::cardinal_t<w_t>{})
                              , &target1[0]
                              , eve::as_aligned(&target2[0], eve::cardinal_t<w_t>{})
                              );

  eve::store(data, dst);

  TTS_ALL_EQUAL(target0, ref0);
  TTS_ALL_EQUAL(target1, ref1);
  TTS_ALL_EQUAL(target2, ref2);

  auto cdst = eve::soa_ptr   ( eve::as_aligned(&ctarget0[0], eve::cardinal_t<w_t>{})
                              , &ctarget1[0]
                              , eve::as_aligned(&ctarget2[0], eve::cardinal_t<w_t>{})
                              );

  {
    ctarget0.fill(5);
    ctarget1.fill(6);
    ctarget2.fill(7);

    eve::store[eve::ignore_last(w_t::size()/2)](data, cdst);

    for(int i = 0; i < w_t::size()/2; ++i)
    {
      TTS_EQUAL(ctarget0[i], ref0[i]);
      TTS_EQUAL(ctarget1[i], ref1[i]);
      TTS_EQUAL(ctarget2[i], ref2[i]);
    }

    for(int i = w_t::size()/2; i != w_t::size(); ++i)
    {
      TTS_EQUAL(ctarget0[i], (std::int8_t)5);
      TTS_EQUAL(ctarget1[i], (T)6);
      TTS_EQUAL(ctarget2[i], 7.0);
    }
  }

  s_t scalar_zero {(std::uint8_t) 0, (T) 0, 0.0};

  // scalar zero
  {
    ctarget0.fill(5);
    ctarget1.fill(6);
    ctarget2.fill(7);

    eve::store[eve::ignore_last(w_t::size()/2).else_(scalar_zero)](data, cdst);

    for(int i = 0; i < w_t::size()/2; ++i)
    {
      TTS_EQUAL(ctarget0[i], ref0[i]);
      TTS_EQUAL(ctarget1[i], ref1[i]);
      TTS_EQUAL(ctarget2[i], ref2[i]);
    }

    for(int i = w_t::size()/2; i != w_t::size(); ++i)
    {
      TTS_EQUAL(ctarget0[i], 0);
      TTS_EQUAL(ctarget1[i], (T)0);
      TTS_EQUAL(ctarget2[i], 0.0);
    }
  }

  w_t wide_zeroes { scalar_zero };

  // wide zeroes
  {
    ctarget0.fill(5);
    ctarget1.fill(6);
    ctarget2.fill(7);

    eve::store[eve::ignore_last(w_t::size()/2).else_(wide_zeroes)](data, cdst);

    for(int i = 0; i < w_t::size()/2; ++i)
    {
      TTS_EQUAL(ctarget0[i], ref0[i]);
      TTS_EQUAL(ctarget1[i], ref1[i]);
      TTS_EQUAL(ctarget2[i], ref2[i]);
    }

    for(int i = w_t::size()/2; i != w_t::size(); ++i)
    {
      TTS_EQUAL(ctarget0[i], 0);
      TTS_EQUAL(ctarget1[i], (T)0);
      TTS_EQUAL(ctarget2[i], 0.0);
    }
  }
};

}
