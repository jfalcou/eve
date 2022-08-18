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
TTS_CASE_TPL("Check return types of asec", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::asec(T()), T);
  TTS_EXPR_IS(eve::asec(v_t()), v_t);
};

//==================================================================================================
// asec  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of asec on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(1.0, 100.0),
                            tts::randoms(1.0, eve::valmax),
                            tts::randoms(eve::valmin, -1.0),
                            tts::randoms(-100.0, -1.0)))
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  auto sasec = [](auto e) -> v_t { return std::acos(1 / e); };
  TTS_ULP_EQUAL(eve::asec(a0), map(sasec, a0), 3.5);

  TTS_ULP_EQUAL(eve::asec(a1), map(sasec, a1), 2);

  TTS_ULP_EQUAL(eve::asec(a2), map(sasec, a2), 2);

  TTS_ULP_EQUAL(eve::asec(a3), map(sasec, a3), 2);
};


//==================================================================================================
// Tests for masked asec
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::asec)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::asec[mask](a0),
            eve::if_else(mask, eve::asec(a0), a0));
};
