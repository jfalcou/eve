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
TTS_CASE_TPL("Check return types of eve::arg(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::arg(T()), T);
  TTS_EXPR_IS(eve::arg[eve::pedantic](T()), T);

  TTS_EXPR_IS(eve::arg(v_t()), v_t);
  TTS_EXPR_IS(eve::arg[eve::pedantic](v_t()), v_t);
};

//==================================================================================================
// Tests for eve::arg
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::arg(simd)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::between(-1.0, 1.0)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  std::cout << "a0 " << a0 << std::endl;
  TTS_EQUAL(eve::arg(a0),
            tts::map([](auto e) -> v_t { return e >= 0 ? 0 : eve::pi(eve::as(v_t())); }, a0));
};

//==================================================================================================
// Tests for eve::arg[eve::pedantic]
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::arg[eve::pedantic](simd)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::between(-1.0, 1.0)))
<typename T>(T a0)
{
  using v_t = eve::element_type_t<T>;

  auto cases = tts::limits(tts::type<T> {});

  TTS_EQUAL(eve::arg[eve::pedantic](a0),
            tts::map([](auto e) -> v_t { return e >= 0 ? 0 : eve::pi(eve::as(v_t())); }, a0));
  TTS_IEEE_EQUAL(eve::arg[eve::pedantic](cases.nan), cases.nan);
};


//==================================================================================================
// Tests for masked arg
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::arg)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::arg[mask](a0),
            eve::if_else(mask, eve::arg(a0), a0));
};
