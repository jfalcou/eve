//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

#include <eve/logical.hpp>
#include <eve/wide.hpp>

//==================================================================================================
// interleave_shuffle test
//==================================================================================================
TTS_CASE_TPL("Check behavior of interleave_shuffle shuffle", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t   = eve::element_type_t<T>;
  constexpr auto cc = T::size() * 2;

  T x{[](int i, int) { return 2*i; }};
  T y{[](int i, int) { return 2*i+1; }};
  v_t sx(2);
  v_t sy(4);
  eve::logical<T> lx{true};
  eve::logical<T> ly{false};


  eve::wide<v_t, cc> ref{[&](int i, int) { return i%2 ? y.get(i/2) : x.get(i/2); }};
  eve::logical<eve::wide<v_t, cc>> lref{[&](int i, int) { return i%2 == 0; }};

  eve::wide<v_t, cc> srefx{[&](int i, int) { return i%2 ? y.get(i/2) : sx; }};
  eve::wide<v_t, cc> srefy{[&](int i, int) { return i%2 ? sy : x.get(i/2); }};


  TTS_EQUAL(ref, eve::interleave_shuffle(x,y));
  TTS_EQUAL(lref, eve::interleave_shuffle(lx,ly));
  TTS_EQUAL(srefx, eve::interleave_shuffle(sx,y));
  TTS_EQUAL(srefy, eve::interleave_shuffle(x,sy));
};
