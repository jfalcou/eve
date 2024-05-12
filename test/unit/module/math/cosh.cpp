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
TTS_CASE_TPL("Check return types of cosh", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::cosh(T()), T);
  TTS_EXPR_IS(eve::cosh(v_t()), v_t);
};

//==================================================================================================
// cosh  tests
//==================================================================================================
auto maxi = []<typename T>(eve::as<T> const&)
{
 return eve::maxlog(eve::as<T>())-eve::log_2(eve::as<T>());
};

auto mini = []<typename T>(eve::as<T> const& tgt) { return -maxi(tgt); };

TTS_CASE_WITH("Check behavior of cosh on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(tts::constant(mini), tts::constant(maxi)),
                            tts::randoms(-1.0, 1.0)))
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  using eve::cosh;
  using eve::sinh;

  TTS_ULP_EQUAL(cosh(a0), map([](auto e) -> v_t { return std::cosh(e); }, a0), 2);
  TTS_ULP_EQUAL(cosh(a1), map([](auto e) -> v_t { return std::cosh(e); }, a1), 2);
};


//==================================================================================================
// Tests for masked cosh
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::cosh)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::cosh[mask](a0),
            eve::if_else(mask, eve::cosh(a0), a0));
};
