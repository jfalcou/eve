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
TTS_CASE_TPL("Check return types of acotpi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::acotpi(T()), T);
  TTS_EXPR_IS(eve::acotpi(v_t()), v_t);
};

//==================================================================================================
// acotpi  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of acotpi on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-1e20, 1e20)))
<typename T>(T const& a0)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(
      eve::acotpi(a0), map([](auto e) -> v_t { return eve::radinpi(std::atan(1 / e)); }, a0), 2);
};


//==================================================================================================
// Tests for masked acotpi
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::acotpi)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::acotpi[mask](a0),
            eve::if_else(mask, eve::acotpi(a0), a0));
};
