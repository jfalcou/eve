//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of asinh", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::asinh(T()), T);
  TTS_EXPR_IS(eve::asinh(v_t()), v_t);
};

//==================================================================================================
// asinh  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of asinh on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::asinh(a0), map([](auto e) -> v_t { return std::asinh(e); }, a0), 2);
};


//==================================================================================================
// Tests for masked asinh
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::asinh)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::asinh[mask](a0),
            eve::if_else(mask, eve::asinh(a0), a0));
};
