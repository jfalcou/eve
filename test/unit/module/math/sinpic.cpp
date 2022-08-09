//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of sinpic"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::sinpic(T())  , T);
  TTS_EXPR_IS( eve::sinpic(v_t()), v_t);
};

//==================================================================================================
// sinpic  tests
//==================================================================================================
auto mini = tts::constant([]<typename T>(eve::as<T> const & tgt) { return eve::valmin(tgt)/4; });
auto maxi = tts::constant([]<typename T>(eve::as<T> const & tgt) { return eve::valmax(tgt)/4; });

TTS_CASE_WITH ( "Check behavior of sinpic on wide"
              , eve::test::simd::ieee_reals
              , tts::generate(tts::randoms(mini, maxi), tts::randoms(-10.0, 10.0))
              )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using eve::sinpic;

  using v_t = eve::element_type_t<T>;
  v_t dpi = 3.1415926535897932384626433832795028841971693993751;
  auto ref = [dpi](auto e) -> v_t { return e ? eve::sinpi(e)/(dpi*e) : v_t(1); };
  TTS_ULP_EQUAL(sinpic(a0), map(ref, a0), 3);
  TTS_ULP_EQUAL(sinpic(a1), map(ref, a1), 3);
};
