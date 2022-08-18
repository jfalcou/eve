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
TTS_CASE_TPL("Check return types of acscpi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::acscpi(T()), T);
  TTS_EXPR_IS(eve::acscpi(v_t()), v_t);
};

//==================================================================================================
// acscpi  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of acscpi on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(1.0, 100.0),
                            tts::randoms(1.0, 1e20),
                            tts::randoms(-1e20, -1.0),
                            tts::randoms(-100.0, -1.0)))
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  auto sacscpi = [](auto e) -> v_t { return eve::radinpi(std::asin(1 / e)); };
  TTS_ULP_EQUAL(eve::acscpi(a0), map(sacscpi, a0), 2);

  TTS_ULP_EQUAL(eve::acscpi(a1), map(sacscpi, a1), 2);

  TTS_ULP_EQUAL(eve::acscpi(a2), map(sacscpi, a2), 2);

  TTS_ULP_EQUAL(eve::acscpi(a3), map(sacscpi, a3), 2);
};


//==================================================================================================
// Tests for masked acscpi
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::acscpi)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::acscpi[mask](a0),
            eve::if_else(mask, eve::acscpi(a0), a0));
};
