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
TTS_CASE_TPL("Check return types of atanpi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::atanpi(T()), T);
  TTS_EXPR_IS(eve::atanpi(v_t()), v_t);
};

//==================================================================================================
// atanpi  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of atanpi on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::randoms(-1.0, 1.0)))
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(
      eve::atanpi(a0), map([](auto e) -> v_t { return eve::radinpi(std::atan(e)); }, a0), 2);
  TTS_ULP_EQUAL(
      eve::atanpi(a1), map([](auto e) -> v_t { return eve::radinpi(std::atan(e)); }, a1), 2);
};


//==================================================================================================
// Tests for masked atanpi
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::atanpi)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::atanpi[mask](a0),
            eve::if_else(mask, eve::atanpi(a0), a0));
};
