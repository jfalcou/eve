//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
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
  T x{[](int i, int) { return 2*i; }};
  T y{[](int i, int) { return 2*i+1; }};
  eve::logical<T> lx{true};
  eve::logical<T> ly{false};

  using v_t   = eve::element_type_t<T>;
  using c_t   = eve::cardinal_t<T>;
  using cc_t  = typename c_t::combined_type;

  eve::wide<v_t,cc_t> ref{[&](int i, int) { return i%2 ? y.get(i/2) : x.get(i/2); }};
  eve::logical<eve::wide<v_t,cc_t>> lref{[&](int i, int) { return i%2 == 0; }};

  TTS_EQUAL(ref, eve::interleave_shuffle(x,y));
  TTS_EQUAL(lref, eve::interleave_shuffle(lx,ly));
};
