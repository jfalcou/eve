//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>


template<typename T>
using tuple_t = kumi::tuple<std::int8_t,T,double>;

//==================================================================================================
// Construct from multiple existing wides
//==================================================================================================
EVE_TEST_TYPES( "Check eve::zip", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using N  = eve::fixed<T::size()>;
  using e_t = eve::element_type_t<T>;
  using w_t = eve::wide<tuple_t<e_t>, N>;
  using s_t = typename eve::wide<tuple_t<e_t>, N>::storage_type;
  using w0_t = std::tuple_element_t<0, s_t>;
  using w1_t = std::tuple_element_t<1, s_t>;
  using w2_t = std::tuple_element_t<2, s_t>;

  w0_t w8{'z'};
  w1_t wt{e_t{45}};
  w2_t wd{13.37};

  TTS_EQUAL(w_t(tuple_t<e_t>{ 'z', e_t{45}, 13.37 }), eve::zip(eve::as<tuple_t<e_t>>(), w8,wt,wd));
  TTS_EQUAL(w_t(tuple_t<e_t>{ 'z', e_t{45}, 13.37 }), eve::zip(w8,wt,wd));

  TTS_EQUAL((tuple_t<e_t>{ 'z', e_t{45}, 13.37 }), eve::zip(eve::as<tuple_t<e_t>>(), 'z', e_t{45}, 13.37));
  TTS_EQUAL((tuple_t<e_t>{ 'z', e_t{45}, 13.37 }), eve::zip('z', e_t{45}, 13.37));
};
