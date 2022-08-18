//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::plus", eve::test::simd::signed_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::plus(T()), T);
  TTS_EXPR_IS(eve::plus(v_t()), v_t);
  if constexpr( eve::floating_real_value<T> ) {}
};


//==================================================================================================
// Tests for masked plus
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::plus)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::plus[mask](a0),
            eve::if_else(mask, eve::plus(a0), a0));
};
